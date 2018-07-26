#include <ros/ros.h>
#include <assignment/SetPosition.h>
#include <assignment/Position.h>
#include <assignment/State.h>

assignment::Position pos;
assignment::State state;
int offset = 0;

void stateCB(const assignment::State::ConstPtr& msg){
	if(state.state != msg->state){
		state = *msg;
		ROS_INFO("Current State is %d", state.state);
	}
}

bool setPosition(assignment::SetPosition::Request& req,
	assignment::SetPosition::Response& res){
	pos.x = req.x;
	pos.y = req.y;
	pos.z = req.z;

	ROS_INFO("New postion (%d, %d, %d) set", pos.x, pos.y, pos.z);
	res.result = true;

	return true;
}

int main(int argc, char **argv){
	ros::init(argc, argv, "position_node");
	ros::NodeHandle nh;

	ros::Publisher position_pub = nh.advertise<assignment::Position>("position", 10);
	ros::Subscriber state_sub = nh.subscribe("state", 10, stateCB);
	ros::ServiceServer set_state_server = nh.advertiseService("set_position", setPosition);
	
	ros::Rate rate(10);

	nh.setParam("offset", 0);

	pos.x = 0;
	pos.y = 0;
	pos.z = 0;

	while(ros::ok()){
		nh.getParam("offset", offset);
		if(state.state == 1){

			pos.x *= -1;
			pos.y *= -1;
			pos.z *= -1;
		}
		else if(state.state == 2){
			pos.x += offset;
			pos.y += offset;
			pos.z += offset;	
		}
		position_pub.publish(pos);
		ros::spinOnce();
		rate.sleep();
	}
	return 0;
}