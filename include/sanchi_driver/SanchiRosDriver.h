#include <string>
#include <queue>

#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/MagneticField.h>
#include <tf/tf.h>

#include <sanchi_driver/SanchiSerialHardware.h>

namespace vwpp
{
    class SanchiRosDriver
    {
    public:
        SanchiRosDriver();
        virtual ~SanchiRosDriver();
        void publishData();
    
    private:

        SanchiSerialHardware* sanchi_serial_hardware;
        std::queue<SanchiSerialHardware::SanchiData> que_sanchi_data_;


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
