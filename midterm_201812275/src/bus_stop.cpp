#include "ros/ros.h"                        
#include "midterm_201812275/passenger.h"
#include "midterm_201812275/board.h"

bool state;

void Callback(const midterm_201812275::board::ConstPtr& msg)
{
  state = msg->board;
  ROS_INFO("state = %d", state);
}

int main(int argc, char **argv){  
  ros::init(argc, argv, "bus_stop");    
  ros::NodeHandle nh;

  ros::Rate loop_rate(1);   

  ros::Subscriber bus_stop_sub = nh.subscribe("get_on", 100, Callback);

  ros::ServiceClient bus_stop_client = nh.serviceClient<midterm_201812275::passenger>("pass");

  midterm_201812275::passenger srv;
  
  while(ros::ok()){
    ros::spinOnce();
    
    //passenger wait at the bus station -> Stop!
    if(state == 1){
        ROS_INFO("There are passengers waiting at the bus station!");
        // pass = false -> Don't pass 
        srv.request.pass = false;
        if (bus_stop_client.call(srv)){
            // action = false -> stop
            if(srv.response.action == false){
                ROS_INFO("Stop!!");
            }
        }
        else {
            ROS_ERROR("Failed to call service passenger_srv");
        }
    }
    // no passenger wait at the bus station -> Pass
    else if(state == 0){
        ROS_INFO("There are no passengers waiting at the bus stop!");
        // pass = true -> Pass
        srv.request.pass = true;
        if (bus_stop_client.call(srv)){
            // action = true -> go
            if(srv.response.action == true){
                ROS_INFO("Pass!!");
            }
        }
        else {
            ROS_ERROR("Failed to call service passenger");
        }
    }
    loop_rate.sleep();
  }
}