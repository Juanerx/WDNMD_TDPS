import sensor, image, time

sensor.reset()
sensor.set_pixformat(sensor.GRAYSCALE)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)

clock = time.clock()
thresholds = (0,53,-128,9,-128,4)

while(True):
    clock.tick()
    img = sensor.snapshot()
    print(clock.fps())

    sample=0
    blobs =img.find_blobs([thresholds], roi=(50,50,50,100), x_stride=10, y_stride=5, invert=False, area_threshold=200, pixels_threshold=180)

    if blobs:
        for b in blobs:
            img.draw_rectangle(b[0:4])
            img.draw_cross(b[5], b[6])
            print(b.density())
            den= b.density()
            if 0.45< den <0.70:
                print ('triangle')
                sample = 2
            elif den > 0.87:
                print ('rectangle')
                sample = 3
            else:
                for c in img.find_circles(threshold = 3500, x_margin = 15, y_margin = 15, r_margin = 15,r_min = 8, r_max = 50, r_step = 2):
                    if 8<c.r()<30:
                        print('circle')
                        sample = 1
