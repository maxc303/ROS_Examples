# Project2
Project: Go chase it

Steps in this project:
* Create my_robot package and a world file for gazebo
* Setup a robot and configure it using URDF. Define the robot in xarco file and add gazebo plugin in gazebo file. Setup a launch file for the urdf robot. The gazebo plugin also have the part of cmd_vel for robot motion.
* Add sensors(Camera and Lidar) and links to the urdf and modify gazebo plugin. Check sensor output in rviz
* Define DriveToTarget Sevice and drive_bot to handle the service to publish motor command
* Define process_images to send drive request when detecting a write ball

### Directory structure
    src
    ├── my_robot                       # my_robot package                   
    │   ├── launch                     # launch folder for launch files   
    │   │   ├── robot_description.launch
    │   │   ├── world.launch
    │   ├── meshes                     # meshes folder for sensors
    │   │   ├── hokuyo.dae
    │   ├── urdf                       # urdf folder for xarco files
    │   │   ├── my_robot.gazebo
    │   │   ├── my_robot.xacro
    │   ├── world                      # world folder for world files
    │   │   ├── <yourworld>.world
    │   ├── CMakeLists.txt             # compiler instructions
    │   ├── package.xml                # package info
    ├── ball_chaser                    # ball_chaser package                   
    │   ├── launch                     # launch folder for launch files   
    │   │   ├── ball_chaser.launch
    │   ├── src                        # source folder for C++ scripts
    │   │   ├── drive_bot.cpp
    │   │   ├── process_images.cpp
    │   ├── srv                        # service folder for ROS services
    │   │   ├── DriveToTarget.srv
    │   ├── CMakeLists.txt             # compiler instructions
    │   ├── package.xml                # package info                  
    └──             