#include "ros/ros.h"
#include "ros_tutorials_topic/MsgTutorial.h"

int main(int argc, char **argv){
	ros::init(argc, argv, "topic_publisher");
	ros::NodeHandle nh;
	ros::Publisher ros_tutorial_pub = nh.advertise<ros_tutorials_topic::MsgTutorial>("ros_tutorial_msg", 100);
	ros::Rate loop_rate(10);
	ros_tutorials_topic::MsgTutorial msg;
	int count = 0;
	while (ros::ok())
	{
		msg.stamp = ros::Time::now();
		msg.data = count;
		// 현재 시간을 msg의 하위 stamp 메시지에 담는다
		// count라는 변수 값을 msg의 하위 data 메시지에 담는다
		ROS_INFO("send msg = %d", msg.stamp.sec);
		ROS_INFO("send msg = %d", msg.stamp.nsec);
		ROS_INFO("send msg = %d", msg.data); // stamp.sec 메시지를 표시한다
		// stamp.nsec 메시지를 표시한다
		// data 메시지를 표시한다
		ros_tutorial_pub.publish(msg); // 메시지를 발행한다
		loop_rate.sleep(); // 위에서 정한 루프 주기에 따라 슬립에 들어간다
		++count; // count 변수 1씩 증가
	}
	return 0;
}