#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <math.h>  

const int PICKUP_X = 2.0;
const int PICKUP_Y = 2.0; 
const int DROPOFF_X = 4.0;
const int DROPOFF_Y = -2.0;
const float DIST_THRESHOLD = 0.1;
float pos_x, pos_y;

// void PoseCallBack(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr &amcl_msg){
//   pos_x = amcl_msg ->pose.pose.position.x;
//   pos_y = amcl_msg ->pose.pose.position.y;
// }

// bool CheckTarget(float init_x,float init_y, float target_x, float target_y){
//   if(sqrt(pow((init_x-target_x)
  
// }

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
//   ros::Subscriber odom_sub = n.subscribe("/amcl_pose", 10, PoseCallBack);
  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;


    visualization_msgs::Marker marker;
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose.position.x = 0;
    marker.pose.position.y = 0;
    marker.pose.position.z = 0;
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 0.3;
    marker.scale.y = 0.3;
    marker.scale.z = 0.3;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 0.0f;
    marker.color.b = 1.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();
    
    marker.pose.position.x = PICKUP_X;
    marker.pose.position.y = PICKUP_Y;
    
   // marker.lifetime = ros::Duration(5);
 	std::string AddMarkerMode = "Pickup";
  	ros::param::get("AddMarkerMode", AddMarkerMode);
  	
  	
  	//Add Marker demo
  	if(AddMarkerMode=="Demo"){
      	ROS_INFO("Add marker test");
       	ros::Duration(5).sleep();

        marker.action = visualization_msgs::Marker::ADD;
        marker_pub.publish(marker);
    	ROS_INFO("Published pickup marker");
      	ros::Duration(5).sleep();
    	marker.action = visualization_msgs::Marker::DELETE;
  		ROS_INFO("Delete pickup marker and wait");
        marker_pub.publish(marker);  
    	ros::Duration(5).sleep();
      
        marker.action = visualization_msgs::Marker::ADD;
        marker.pose.position.x = DROPOFF_X;
        marker.pose.position.y = DROPOFF_Y;
        marker.lifetime = ros::Duration();
        marker_pub.publish(marker);
        ROS_INFO("Published dropoff marker");
        ros::Duration(5).sleep();
		return 0;
    }
  
  	//Home Service Robot if not demo
    marker_pub.publish(marker);
    ROS_INFO("Published pickup marker");
    while(AddMarkerMode=="Pickup"){
        marker_pub.publish(marker);
		ROS_INFO("Published pickup marker");
        ros::Duration(1).sleep();
        ros::param::get("AddMarkerMode", AddMarkerMode);
    }
  	
    marker.action = visualization_msgs::Marker::DELETE;
  	ROS_INFO("Delete pickup marker and wait");
  
        marker_pub.publish(marker);  
    ros::Duration(5).sleep();
    
    
    while(AddMarkerMode=="Wait"){
		ROS_INFO("Waiting the robot");
        ros::Duration(1).sleep();
        ros::param::get("AddMarkerMode", AddMarkerMode);
    }

     marker.action = visualization_msgs::Marker::ADD;
    marker.pose.position.x = DROPOFF_X;
    marker.pose.position.y = DROPOFF_Y;
    marker.lifetime = ros::Duration();
    marker_pub.publish(marker);
  	ROS_INFO("Published dropoff marker");
	ros::Duration(5).sleep();

 
  return 0;

}
