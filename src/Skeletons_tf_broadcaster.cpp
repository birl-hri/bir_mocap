#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <birl_mocap/SkeletonArray.h>
#include <birl_mocap/Skeleton.h>
#include <birl_mocap/RigidBody.h>
#include <birl_mocap/RigidBodyArray.h>

/* 
@author Xiaohan Chen , Biomimetic and Intelligent Robotics Lab, Guangdong University of Technology 
*/

/*A simple node for showing skeletons in robot scense(rviz)*/

/*Don't expect it to work well*/

void SkCallback(const birl_mocap::SkeletonArrayConstPtr &msg)
{
	static tf::TransformBroadcaster mocap_world_br;
	static tf::TransformBroadcaster br;

	tf::Transform transform;
	/* set transform between robot world and mocap_world */
	transform.setOrigin(
			tf::Vector3(-2.5,3,-0.7));
	tf::Quaternion q;
	q.setRPY(1.57, 0, -1.57);

	transform.setRotation(q);

	mocap_world_br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "world", "mocap_world"));

	std::size_t RB_num = msg->Skeleton[0].RigidBody.size();

	for(std::size_t RB_idx = 0;RB_idx <RB_num; ++RB_idx)
	{
		tf::Transform transform;
		birl_mocap::RigidBody RB = msg->Skeleton[0].RigidBody[RB_idx];

		transform.setOrigin(
			tf::Vector3(
				RB.pose.position.x,
				RB.pose.position.y,
				RB.pose.position.z
				));
		transform.setRotation(
			tf::Quaternion(
				RB.pose.orientation.x,
				RB.pose.orientation.y,
				RB.pose.orientation.z,
				RB.pose.orientation.w
				));
	br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "mocap_world", RB.name));
	}
}



int main(int argc, char **argv)
{
	// 初始化ROS节点
	ros::init(argc, argv, "Skeletons_tf_broadcaster");

	ros::NodeHandle node;
	ros::Subscriber sub = node.subscribe("/birl/mocap/Skeletons", 10, SkCallback);

	// 循环等待回调函数
	ros::spin();

	return 0;
};
