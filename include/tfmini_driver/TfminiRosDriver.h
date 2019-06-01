#ifndef TFMINIROSDRIVER_H_
#define TFMINIROSDRIVER_H_

#include <string>
#include <queue>

#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/MagneticField.h>
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
        sensor_msgs::Imu msg_imu;
        sensor_msgs::MagneticField msg_mag;

        ros::NodeHandle nh;
        ros::Publisher imu_pub;
        ros::Publisher mag_pub;
    };
    
} // namespace vwpp

#endif
