#include "ros/ros.h"                          
#include "midterm_201812275/detect.h"

bool brake_response(midterm_201812275::detect::Request &req,
                 midterm_201812275::detect::Response &res)
{
  if(req.stop == false){
    ROS_INFO("Okay! I did!");
    res.action = true;
  }
  else{
    ROS_INFO("Okay! I still go!");
    res.action = false;
  }
  return true;
}

int main(int argc, char **argv)            
{
  ros::init(argc, argv, "motor_node");   
  ros::NodeHandle nh;                       

  ros::ServiceServer ros_tutorials_service_server = nh.advertiseService("detect_signal", brake_response);

  ROS_INFO("ready srv server!");

  ros::spin();   
}