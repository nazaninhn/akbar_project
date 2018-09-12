#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <sstream>
#include "turtlesim/Pose.h"

int x,y;
int a,b;
geometry_msgs::Twist message;

void chatterCallback(const geometry_msgs::Twist::ConstPtr& msg)
{
 message.linear.x= msg->linear.x;
 message.linear.y= msg->linear.y;
message.angular.x =msg->angular.x;
message.angular.y =msg->angular.y;

  ROS_INFO("I heard: [%f],[%f]", x,y);
}

void chatterCallback1(const geometry_msgs::Twist::ConstPtr& msg)
{
// a=msg.linear.x;
// b=msg.linear.y;
  //ROS_INFO("I heard: [%f],[%f]",a,b);
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "talis");

  
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("turtle1/cmd_vel", 1000, &chatterCallback);
 // ros::Subscriber sub1 = n.subscribe("akbar/cmd_vel", 1000, &chatterCallback1);

  
  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("akbar/cmd_vel", 1000);

  ros::Rate loop_rate(10);
  int count = 0;


  while (ros::ok())
  {
    geometry_msgs::Twist msg;
    
    msg.linear.x=message.linear.x;
    msg.linear.y=message.linear.y;
    
    msg.angular.x=message.angular.x;
    msg.angular.y=message.angular.y;
    ROS_INFO("lab lab %f  %f",msg.linear.x,msg.linear.y );

    
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
