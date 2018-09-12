#include "ros/ros.h"
#include "std_msgs/String.h"
#include "geometry_msgs/Twist.h"
#include <sstream>
#include "turtlesim/Pose.h"

int x,y;
int a,b;

void chatterCallback(const turtlesim::Pose::ConstPtr& msg)
{
 x=msg->x;
 y=msg->y;
  ROS_INFO("I heard: [%f],[%f]", x,y);
}

void chatterCallback1(const turtlesim::Pose::ConstPtr& msg)
{
 a=msg->x;
 b=msg->y;
  ROS_INFO("I heard: [%f],[%f]",a,b);
}

int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "talis");

  
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("turtle1/pose", 1000, &chatterCallback);
  ros::Subscriber sub1 = n.subscribe("akbar/pose", 1000, &chatterCallback1);

  
  ros::Publisher chatter_pub = n.advertise<geometry_msgs::Twist>("akbar/cmd_vel", 1000);

  ros::Rate loop_rate(10);
  int count = 0;


  while (ros::ok())
  {
    geometry_msgs::Twist msg;

    msg.linear.x=x-a;
    msg.linear.y=y-b;

    ROS_INFO("%f  %f",x-a,y-b );

    
    chatter_pub.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}
