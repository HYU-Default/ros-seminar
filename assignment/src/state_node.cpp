#include <ros/ros.h>
#include <assignment/SetState.h>
#include <assignment/Position.h>
#include <assignment/State.h>

assignment::State state;
assignment::Position pos;

bool setState(assignment::SetState::Request& req,
	assignment::SetState::Response& res){
	if((req.state > -1) && (req.state < 3)){
		state.state = req.state;
		ROS_INFO("State is changed to %d", state.state);
		res.result = true;
		return true;
	}
	else{
		res.result = false;
		return false;
	}
}

void positionCB(const assignment::Position::ConstPtr& msg){
	if((pos.x != msg->x) || (pos.y != msg->y) || (pos.z != msg->z)){
		pos = *msg;
		ROS_INFO("Current position : (%d, %d, %d)", pos.x, pos.y, pos.z);
	}
}

int main(int argc, char **argv){
	ros::init(argc, argv, "assign_state_node");
	ros::NodeHandle nh;

	ros::Publisher state_pub = nh.advertise<assignment::State>("state", 10);
	ros::Subscriber position_sub = nh.subscribe("position", 10, positionCB);
	ros::ServiceServer set_state_server = nh.advertiseService("set_state", setState);

	ros::Rate rate(10);

	state.state = 0;

	while(ros::ok()){
		if(((pos.x > 5) || (pos.y > 5) || (pos.z > 5)) && (state.state != 1)){
			ROS_INFO("Position > 5!! State set 1");
			state.state = 1;
		}
		else if(((pos.x < -20) || (pos.y < -20) || (pos.z < -20)) && (state.state != 2)){
			ROS_INFO("Position < -20!! State set 2");
			state.state = 2;
		}
		state_pub.publish(state);
		ros::spinOnce();
		rate.sleep();
	}

	return 0;
}