#include <ros/ros.h>
#include <actionlib/client/simple_action_client.h>
#include <actionlib/client/terminal_state.h>
#include <midterm_201812275/positionAction.h>

int num = 1;

int main (int argc, char **argv){
    ros::init(argc, argv, "passenger");
    ros::NodeHandle nh;

    actionlib::SimpleActionClient<midterm_201812275::positionAction> ac("pos", true);

    ROS_INFO("Waiting for action server to start.");
    ac.waitForServer();

    ROS_INFO("Action server started, sending goal.");
    nh.param("destination", num, 1);

    midterm_201812275::positionGoal goal;
    goal.dst = num;
    ac.sendGoal(goal);

    bool finished_before_timeout = ac.waitForResult(ros::Duration(100.0));

    if (finished_before_timeout){
        actionlib::SimpleClientGoalState state = ac.getState();
        ROS_INFO("Get off!");
    }
    else{
        ROS_INFO("Action did not finish before the time out.");
    }
    return 0;
 }
