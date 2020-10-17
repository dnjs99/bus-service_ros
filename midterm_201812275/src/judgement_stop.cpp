#include "ros/ros.h"                          
#include "midterm_201812275/passenger.h"

bool brake_response(midterm_201812275::passenger::Request &req,
                 midterm_201812275::passenger::Response &res)
{
  if(req.pass == false){
    ROS_INFO("Okay! I'm gonna stop!!");
    res.action = false;
  }
  else{
    ROS_INFO("Okay! I'm gonna pass!!");
    res.action = true;
  }
  return true;
}

int main(int argc, char **argv)            
{
  ros::init(argc, argv, "passenger_perception");   
  ros::NodeHandle nh;                       

  ros::ServiceServer ros_tutorials_service_server = nh.advertiseService("pass", brake_response);

  ROS_INFO("ready srv server!");

  ros::spin();   
}