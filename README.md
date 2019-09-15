# nd209-go-chase-it
This is a ROS project, part of the Udacity Robotics Nanodegree program.

# Build
Go to your catkin workspace:
```
cd /path/to/catkin_ws
```
Clone the repository and run
`catkin_make`

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
