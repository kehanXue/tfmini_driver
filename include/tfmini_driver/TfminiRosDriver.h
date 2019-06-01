#ifndef TFMINIROSDRIVER_H_
#define TFMINIROSDRIVER_H_

#include <string>
#include <queue>

#include <ros/ros.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>
#include <std_msgs/Int8.h>
#include <tf/tf.h>

#include <tfmini_driver/TfminiSerialHardware.h>

namespace vwpp
{
    class TfminiRosDriver
    {
    public:
        TfminiRosDriver();
        virtual ~TfminiRosDriver();
        void publishData();
    
    private:

        TfminiSerialHardware* tfmini_serial_hardware;
        std::queue<TfminiSerialHardware::TfminiData> que_tfmini_data_;


        std::string node_name;
        std::string model;
        std::string port;
        int baud;
        int msg_length;

        std::string frame_id;
        std_msgs::Float32 msg_dist;
        std_msgs::Int32 msg_strength;
        std_msgs::Int8 msg_mode;

        ros::NodeHandle nh;
        ros::Publisher dist_pub;
        ros::Publisher strength_pub;
        ros::Publisher mode_pub;
    };
    
} // namespace vwpp

#endif
