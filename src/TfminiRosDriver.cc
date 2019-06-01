#include <tfmini_driver/TfminiRosDriver.h>

using namespace std;
using namespace vwpp;

TfminiRosDriver::TfminiRosDriver():
    nh(ros::NodeHandle("~")),
    model("100D2"),
    port("/dev/ttyUSB0"),
    baud(115200),
    frame_id("imu_link"),
    msg_length(40)
{
    this->node_name = ros::this_node::getName();

    if (nh.hasParam("model"))
    {
        nh.getParam("model", this->model);
        ROS_INFO("%s, use model %s", this->node_name.c_str(), this->model.c_str());
    }
    else
    {
        ROS_WARN("%s, use the default model %s", this->node_name.c_str(), this->model.c_str());
    }


    if (nh.hasParam("port"))
    {
        nh.getParam("port", this->port);
        ROS_INFO("%s, use port %s", this->node_name.c_str(), this->port.c_str());
    }
    else
    {
        ROS_WARN("%s, use the default port %s", this->node_name.c_str(), this->port.c_str());
    }
    
    if (nh.hasParam("baud"))
    {
        nh.getParam("baud", this->baud);
        ROS_INFO("%s, use baud %d", this->node_name.c_str(), this->baud);
    }
    else
    {
        ROS_WARN("%s, use the default baud %d", this->node_name.c_str(), this->baud);
    }

    if (nh.hasParam("msg_length"))
    {
        nh.getParam("msg_length", this->msg_length);
        ROS_INFO("%s, msg_length %d", this->node_name.c_str(), this->msg_length);
    }
    else
    {
        ROS_WARN("%s, use the default msg_length %d", this->node_name.c_str(), this->msg_length);
    }

    this->tfmini_serial_hardware = new TfminiSerialHardware(this->model,
                                                    this->port,
                                                    this->baud,
                                                    this->msg_length);

    if (nh.hasParam("frame_id"))
    {
        nh.getParam("frame_id", this->frame_id);
        ROS_INFO("%s, use frame_id %s", this->node_name.c_str(), this->frame_id.c_str());
    }
    else
    {
        ROS_WARN("%s, use the default frame_id %s", this->node_name.c_str(), this->frame_id.c_str());
    }

    // TODO: Consider add to the initial list.
    std::string imu_pub_topic_name = "imu";
    std::string mag_pub_topic_name = "imu_mag";
    if (nh.hasParam("imu_topic"))
    {
        nh.getParam("imu_topic", imu_pub_topic_name);
        ROS_INFO("%s, use imu_topic name %s", this->node_name.c_str(), imu_pub_topic_name.c_str());
    }
    else
    {
        ROS_WARN("%s, use the default imu_topic name %s", this->node_name.c_str(), imu_pub_topic_name.c_str());
    }
    if (nh.hasParam("mag_topic"))
    {
        nh.getParam("mag_topic", mag_pub_topic_name);
        ROS_INFO("%s, use mag_topic name %s", this->node_name.c_str(), mag_pub_topic_name.c_str());
    }
    else
    {
        ROS_WARN("%s, use the default mag_port name %s", this->node_name.c_str(), mag_pub_topic_name.c_str());
    }
    imu_pub = nh.advertise<sensor_msgs::Imu>(imu_pub_topic_name, 1);
    mag_pub = nh.advertise<sensor_msgs::MagneticField>(mag_pub_topic_name, 1);


}



TfminiRosDriver::~TfminiRosDriver()
{
    delete this->tfmini_serial_hardware;
}



void TfminiRosDriver::publishData()
{
    this->que_tfmini_data_ = this->tfmini_serial_hardware->readData();
    if (this->que_tfmini_data_.size() == 1 || this->que_tfmini_data_.size() == 2)
    {
        while( !(this->que_tfmini_data_.empty()) )
        {

            this->msg_imu.header.stamp = ros::Time::now();
            this->msg_imu.header.frame_id = this->frame_id;

            this->msg_imu.orientation.w = this->que_tfmini_data_.front().q_.w;
            this->msg_imu.orientation.x = this->que_tfmini_data_.front().q_.x;
            this->msg_imu.orientation.y = this->que_tfmini_data_.front().q_.y;
            this->msg_imu.orientation.z = this->que_tfmini_data_.front().q_.z;

            this->msg_imu.angular_velocity.x = this->que_tfmini_data_.front().av_.x;
            this->msg_imu.angular_velocity.y = this->que_tfmini_data_.front().av_.y;
            this->msg_imu.angular_velocity.z = this->que_tfmini_data_.front().av_.z;

            this->msg_imu.linear_acceleration.x = this->que_tfmini_data_.front().la_.x;
            this->msg_imu.linear_acceleration.y = this->que_tfmini_data_.front().la_.y;
            this->msg_imu.linear_acceleration.z = this->que_tfmini_data_.front().la_.z;

            this->imu_pub.publish(this->msg_imu);


            this->msg_mag.header.stamp = this->msg_imu.header.stamp;
            this->msg_mag.header.frame_id = this->msg_imu.header.frame_id;
            this->msg_mag.magnetic_field.x = this->que_tfmini_data_.front().mf_.x;
            this->msg_mag.magnetic_field.y = this->que_tfmini_data_.front().mf_.y;
            this->msg_mag.magnetic_field.z = this->que_tfmini_data_.front().mf_.z;

            this->mag_pub.publish(this->msg_mag);

            this->que_tfmini_data_.pop();
        }
    }
}
