# 结合了道路中线算法和道路中点算法

import sensor, image, time, math
from pid import PID
from pyb import UART, LED

sensor.reset()                      # Reset and initialize the sensor.
sensor.set_pixformat(sensor.GRAYSCALE) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (320x240)
sensor.skip_frames(time = 2000)     # Wait for settings take effect.
clock = time.clock()                # Create a clock object to track the FPS.

rho_weight = 1
theta_weight = 1
count = 0
w = 80
h = 60
mid_x = w/2
mid_y = h/2
gain = 5

uart = UART(3, 115200)
green_led = LED(2)

def pooling_filter(img):
    img.midpoint_pool(2, 2,bias=0.5)
    img.binary([(120,130)])
    img.midpoint_pool(2, 2,bias=0.5)
    img.binary([(120,130)])
#w:80,h:60

def find_middle_line(img):
    '''
    拟合道路中线算法，返回偏差的距离:rho_error和中线的角度:theta_error
    '''
    try: #拟合在某种极端情况下可能会报错，防止因为拟合报错而停止程序
        pooling_filter(img) # 池化两次
        line = img.get_regression([(240,255)], robust = True) #得到道路中线
        img.draw_line(line.line(), color = 139,thickness=2)
        rho_error, theta_error = line_to_theta_and_rho(line.rho(),line.theta())
        #print('rho_error=',rho_error,'theta_error=',theta_error)
        return rho_error, theta_error
    except:
        return 0,0

def line_to_theta_and_rho(rho,theta):
    if rho < 0:
        trans_rho = -rho
        trans_theta = theta + 180
    else:
        trans_rho = rho
        trans_theta = theta

    cos_trans_theta = math.cos(math.radians(trans_theta))
    sin_trans_theta = math.sin(math.radians(trans_theta))

    distance = abs(mid_x*cos_trans_theta + mid_y*sin_trans_theta - trans_rho)

    if trans_theta == 90 or trans_theta == 270:
        distance_error = theta_error = 0
    elif (trans_rho-mid_y*sin_trans_theta)/cos_trans_theta > mid_x: #第一、四象限
        distance_error = distance
        if theta > 90:
            theta_error = theta - 180
        else:
            theta_error = theta
    else:                                                   #第二、三象限
        distance_error = -distance
        if theta > 90:
            theta_error = theta - 180
        else:
            theta_error = theta

    return distance_error, theta_error

def mapping(pid_ouput):
    if -10<=pid_ouput<=10:      #直行
        command = 'A'
    elif -30<=pid_ouput<-10:    #直左
        command = 'B'
    elif 10<pid_ouput<=30:      #直右
        command = 'C'
    elif -100<=pid_ouput<-30:   #左转
        command = 'D'
    elif 30<pid_ouput<=100:     #右转
        command = 'E'
    elif pid_ouput<-100:        #大左
        command = 'F'
    else:                       #大右
        command = 'G'
    return command

while(True):
    clock.tick()                    # Update the FPS clock.
    img = sensor.snapshot()         # Take a picture and return the image.
    img.find_edges(image.EDGE_CANNY, threshold=(150,190))
    rho_error,theta_error = find_middle_line(img)

    #接收stm32 data
    if uart.any():
        a = uart.readchar()
        print ("\r\nInformation from STM32:\r\n")
        print (a)

    #以3为周期取结果平均
    if count != 3:
        if count == 0:
            rho_error_sum = theta_error_sum = 0
        rho_error_sum += rho_error
        theta_error_sum += theta_error
        count += 1
        continue
    else:
        rho_error_sum /= 3
        theta_error_sum /= 3
        count = 0

    #计算PID
    rho_pid = PID(p=0.40, i=0.1, d=0, imax=10) # 0~50
    theta_pid = PID(p=0.30, i=0.1, d=0, imax=10) # -90 ~ 90
    rho_output = rho_pid.get_pid(rho_error_sum,1)
    #print('rho_output=',rho_output)
    theta_output = theta_pid.get_pid(theta_error_sum,1)
    #print('theta_output=',theta_output)
    pid_output = gain*int(rho_weight*rho_output+theta_weight*theta_output)

    # UART传输数据
    command = mapping(pid_output)
    uart.write(str(command)+'\r\n')
    print('pid_output=',pid_output,'command=',command)

    #亮绿灯表示openmv正常运行
    green_led.on()
