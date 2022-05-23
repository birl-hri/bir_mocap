# birl_mocap

A ROS package for receiving the data stream send by Optitrack Motive.

This package can connect to a NatNet server, receive a data stream, and publish that data stream (only RigidBody and Skeleton actually) by ros topic. 

Usage [optional]:

	rosrun birl_mocap birl_mocap [ServerIP] [LocalIP] 

	[ServerIP] IP address of the server (e.g. 192.168.0.107) ( defaults to local machine)

    or 

    1.      rosrun birl_mocap birl_mocap
    2.      Select the server you want to connect to


IMPORTANT!!!

1. If the compilation fails, please comment following in CMakeLists.txt, then recompile to bulid dependencies(msg)

	add_executable(birl_mocap src/birl_mocap.cpp)
	target_link_libraries(birl_mocap ${catkin_LIBRARIES} NatNetLibShared)
	add_executable(Sk_tf_broadcaster src/Skeletons_tf_broadcaster.cpp)
	target_link_libraries(Sk_tf_broadcaster ${catkin_LIBRARIES} NatNetLibShared)

2. Then cancel the above comments and recompile


