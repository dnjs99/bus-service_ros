#! /usr/bin/env python

import rospy
from midterm_201812275.msg import info
from midterm_201812275.msg import board
import random

pub = rospy.Publisher('get_on', board, queue_size=100)

boarding = 0

def callback(data):
    rospy.loginfo("time : %d, pos : %d", data.time, data.pos)
    # num = random.randint(0, 2)
    if data.time == 50:
        global boarding
        # pass the bus station
        # if num == 1:
            # boarding = 0
            # rospy.loginfo("False!")
        # stop the bus station
        # else:
        boarding = 1
        rospy.loginfo("True!")
    pub.publish(boarding)



while not rospy.is_shutdown():
    rospy.init_node('smartphone')
    sub = rospy.Subscriber('info', info, callback)

    rospy.spin()

    