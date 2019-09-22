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
And to run the chaser nodes, run:
```
roslaunch ball_chaser ball_chaser.launch
```
Select the white ball outside the world, and place infront of the robot. The robot should drive towards the ball.
