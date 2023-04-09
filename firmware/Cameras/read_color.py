# Single Color RGB565 Blob Tracking Example
#
# This example shows off single color RGB565 tracking using the OpenMV Cam.

import sensor, image, time, math

threshold_index = 3 # 0 for red, 1 for green, 2 for blue

# Color Tracking Thresholds (L Min, L Max, A Min, A Max, B Min, B Max)
# The below thresholds track in general red/green/blue things. You may wish to tune them...
thresholds = [(0, 100, 18, 36, 7, 22), # generic_red_thresholds
              (0, 100, -28, -11, 3, 20), # generic_green_thresholds
              (0, 100, -20, -5, 13, 51)]

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time = 2000)
sensor.set_auto_gain(False) # must be turned off for color tracking
sensor.set_auto_whitebal(False) # must be turned off for color tracking
clock = time.clock()

# Only blobs that with more pixels than "pixel_threshold" and more area than "area_threshold" are
# returned by "find_blobs" below. Change "pixels_threshold" and "area_threshold" if you change the
# camera resolution. "merge=True" merges all overlapping blobs in the image.

while(True):
    clock.tick()
    img = sensor.snapshot()
    #for blob in
    #print(len(img.find_blobs([thresholds[threshold_index]], pixels_threshold=200, area_threshold=200, merge=True, )))
    #print(img.find_blobs([thresholds[0]], pixels_threshold=200, area_threshold=200, merge=True, margin = 10))
    #print(img.find_blobs([thresholds[1]], pixels_threshold=200, area_threshold=200, merge=True, margin = 10))
    #print(img.find_blobs([thresholds[2]], pixels_threshold=1000, area_threshold=200, merge=True, margin = 10))
        ## These values depend on the blob not being circular - otherwise they will be shaky.
        #if blob.elongation() > 0.5:
            #img.draw_edges(blob.min_corners(), color=(255,0,0))
            #img.draw_line(blob.major_axis_line(), color=(0,255,0))
            #img.draw_line(blob.minor_axis_line(), color=(0,0,255))
        ## These values are stable all the time.
        #img.draw_rectangle(blob.rect())
        #img.draw_cross(blob.cx(), blob.cy())
        ## Note - the blob rotation is unique to 0-180 only.
        #img.draw_keypoints([(blob.cx(), blob.cy(), int(math.degrees(blob.rotation())))], size=20)
    #print(clock.fps())
