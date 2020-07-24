#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

const int PICKUP_X = 2.0;
const int PICKUP_Y = 2.0; 
const int DROPOFF_X = 4.0;
const int DROPOFF_Y = -2.0;
int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");
  ROS_INFO("ROS Init");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal pickup_goal;
  move_base_msgs::MoveBaseGoal dropoff_goal;
  // set up the frame parameters
  pickup_goal.target_pose.header.frame_id = "map";
  pickup_goal.target_pose.header.stamp = ros::Time::now();

  dropoff_goal.target_pose.header.frame_id = "map";
  dropoff_goal.target_pose.header.stamp = ros::Time::now();
  
  // Define a position and orientation for the robot to reach
  pickup_goal.target_pose.pose.position.x = PICKUP_X;
  pickup_goal.target_pose.pose.position.y = PICKUP_Y;
  pickup_goal.target_pose.pose.orientation.w =1.0;

  
   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending pickup goal");
  ac.sendGoal(pickup_goal);

  
  // Wait an infinite time for the results
  ac.waitForResult();
  ros::param::set("AddMarkerMode", "Pickup");
  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("The base has reached the pickup zone");
    ros::param::set("AddMarkerMode", "Wait");

  }else{
    ROS_INFO("The base failed to move to pickup zone for some reason");
    return 1;
  }
  
  
  //Drop off process
  dropoff_goal.target_pose.pose.position.x = DROPOFF_X;
  dropoff_goal.target_pose.pose.position.y = DROPOFF_Y;
  dropoff_goal.target_pose.pose.orientation.w =1.0;
  
  ros::Duration(5).sleep();
  ROS_INFO("Sending drop off goal");
  ac.sendGoal(dropoff_goal);
  ac.waitForResult();
    
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("The base has reached the drop off zone");
       ros::param::set("AddMarkerMode", "Dropoff");
  }else{
    ROS_INFO("The base failed to move to drop pff zone for some reason");
    return 1;
  }
  
  return 0;
  
  
  
  
}