#! /usr/bin/env python

import rospy
import math
from sensor_msgs.msg import LaserScan
from midterm_201812275.srv import detect, detectResponse

degree = 0.0
distance = 0.0

def callback(data):
    count = int(data.scan_time / data.time_increment)
    for i in range(count):
        global degree
        global distance
        degree = math.degrees(data.angle_min + data.angle_increment * i) + 180
        distance = data.ranges[i]
        # if(distance > 0.33 and distance < 6.5):
        #     rospy.loginfo("degree : %f, distance : %f" %(degree, distance))

def detect_station():
    rospy.wait_for_service('detect_signal')
    try:
        state = rospy.ServiceProxy('detect_signal', detect)
        if distance < 2.0:
            rospy.loginfo("Detect the Bus station! Stop!")
            resp = state(stop = False)
        else:
            rospy.loginfo("Do not Detect the Bus station! Pass!")
            resp = state(stop = True)
            return resp.action
    except rospy.ServiceException as e :
        rospy.loginfo("Service acll failed : %s" %e)

if __name__ == '__main__':
    rospy.init_node('detect_station')
    sub = rospy.Subscriber('scan', LaserScan, callback)

    rospy.loginfo("Ready to detect Bus stop")

    detect_station()

    rospy.spin()

    