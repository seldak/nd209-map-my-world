# nd209-where-am-i
This is a ROS project, part of the Udacity Robotics Nanodegree program. This was developed under ROS Kinetic.

# Build
Go to your catkin workspace:
```
cd /path/to/catkin_ws
```
Clone the repository and run
```
git submodule init
git submodule update
catkin_make
```

# Run
After building, launch Gazebo and Rviz:
```
roslaunch my_robot world.launch
```
Launch the adaptive Monte Carlo Localization node:
```
roslaunch my_robot amcl.launch
```
Then launch the teleop twist keyboard script to navigate.

[Screenshot](screenshot.gif)
