#include <ros/ros.h>
#include <assignment/Position.h>
#include <assignment/State.h>

assignment::State state;
assignment::Position pos;

void positionCB(const assignment::Position::ConstPtr& msg){
	if((pos.x != msg->x) || (pos.y != msg->y) || (pos.z != msg->z)){
		pos = *msg;
		ROS_INFO("Current position : (%d, %d, %d)", pos.x, pos.y, pos.z);
	}
}

void stateCB(const assignment::State::ConstPtr& msg){
	if(state.state != msg->state){
		state = *msg;
		ROS_INFO("Current State is %d", state.state);
	}
}

int main(int argc, char **argv){
	ros::init(argc, argv, "listener");
	ros::NodeHandle nh;

	ros::Subscriber position_sub = nh.subscribe("position", 10, positionCB);
	ros::Subscriber state_sub = nh.subscribe("state", 10, stateCB);

	ros::spin();
	return 0;
}