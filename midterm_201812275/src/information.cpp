#include "ros/ros.h"                          
#include "midterm_201812275/info.h"
#include <actionlib/server/simple_action_server.h>
#include <midterm_201812275/positionAction.h>

class INFOAction{
    protected:
        ros::NodeHandle nh_;
        actionlib::SimpleActionServer<midterm_201812275::positionAction> as_;

        std::string action_name_;

        midterm_201812275::positionFeedback feedback_;
        midterm_201812275::positionResult result_;

    public:
        INFOAction(std::string name) : as_(nh_, name, boost::bind(&INFOAction::infoPos, this, _1), false),
            action_name_(name){
                as_.start();
            }
        
        ~INFOAction(void) {}

        void infoPos(const midterm_201812275::positionGoalConstPtr& goal){
          ros :: Rate r(5);
          bool success = true;
          int dis = 50 * goal->dst;
          feedback_.pos = abs(dis);

          ROS_INFO("%s : Excuting, goal : %d, receive data : %d", 
          action_name_.c_str(), goal->dst, dis);

          for(int i = 0; i < dis; i++){
            if(as_.isPreemptRequested() || !ros::ok()){
              ROS_INFO("%s : Preempted", action_name_.c_str());
              as_.setPreempted();
              success = false;
            }
            feedback_.pos--;
            as_.publishFeedback(feedback_);
            r.sleep();
          }

          if (success){
            result_.arrival = true;
            ROS_INFO("We've arrived at our destination!");
            as_.setSucceeded(result_);
          }
        }
};

int main(int argc, char **argv)             
{
  ros::init(argc, argv, "information");     
  ros::NodeHandle nh;

  ros::Publisher info_pub = nh.advertise<midterm_201812275::info>("info", 100);

  ros::Rate loop_rate(5);

  INFOAction position("pos");

  midterm_201812275::info msg;
  int pos = 50;
  int time = 100;
  
  while (ros::ok()){   
    ros::spinOnce();      
    msg.pos  = pos;
    msg.time = time;

    ROS_INFO("send pos = %d", msg.pos); 
    ROS_INFO("send time = %d", msg.time);

    if(pos == 0 || time == 0){
        pos = 50;
        time = 100;
    }
    else{
        if((time % 2)==0){ pos--; }
        time--;
    }

    info_pub.publish(msg); 

    loop_rate.sleep();
  }
  return 0;
}