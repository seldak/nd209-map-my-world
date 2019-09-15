#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    // Request a service and pass the velocities to it to drive the robot
    //ROS_INFO_STREAM("Driving Robot");

    ball_chaser::DriveToTarget srv;
    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    // Call the safe_move service and pass the requested joint angles
    if (!client.call(srv))
        ROS_ERROR("Failed to call service drive_robot");
}

bool check_pixel(const std::vector<uint8_t> &data, uint32_t pos, uint32_t value)
{
    return ( data[pos] == value &&
             data[pos+1] == value &&
             data[pos+2] == value ) ? true : false;
}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{
    const uint8_t white_pixel = 255;
    bool white_ball_exists = false;
    float linear_x = 0.0;
    float angular_z = 0.0;
    uint32_t i = 0;
    uint32_t j = 0;

    // Loop through each pixel in the image and check if there's a bright white one
    for( i = 0; i < img.height; i++ ) {
        for( j = 0; j < img.width; j++ ) {
            if( check_pixel( img.data, i*img.step + j*3, white_pixel ) ) {
                // Check surrounding pixels if they are the same color
                if( check_pixel( img.data, i*img.step + (j+1)*3, white_pixel ) &&
                    check_pixel( img.data, (i+1)*img.step + j*3, white_pixel ) ){
                    // Check upper and left pixels (if in existing range)
                    if( i > 0 && check_pixel( img.data, (i-1)*img.step + j*3, white_pixel ) ) {
                        if( j > 0 && check_pixel( img.data, i*img.step + (j-1)*3, white_pixel ) ) {
                            white_ball_exists = true;
                            break;
			}
                    }
                }
            }
        }
        if( white_ball_exists )
            break;
    }

    // Identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera
    if( white_ball_exists ) {
        linear_x = 0.2;
        if( j < img.width / 3 )
            angular_z = M_PI / (6 * 5);
        else if( j > 2 * img.width / 3 )
            angular_z = -M_PI / (6 * 5);
    }

    drive_robot(linear_x, angular_z);
}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}

