#include <tfmini_driver/TfminiRosDriver.h>

using namespace std;
using namespace vwpp;

TfminiRosDriver::TfminiRosDriver():
    nh(ros::NodeHandle("~")),
    model("tfmini"),
    port("/dev/ttyUSB0"),
    baud(115200),
    frame_id("tfmini_link"),
    msg_length(9)
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
    std::string dist_pub_topic_name = "dist";
    std::string strength_pub_topic_name = "strength";
    std::string mode_pub_topic_name = "mode";
    if (nh.hasParam("dist_topic"))
    {
        nh.getParam("dist_topic", dist_pub_topic_name);
        ROS_INFO("%s, use dist_topic name %s", this->node_name.c_str(), dist_pub_topic_name.c_str());
    }
    else
    {
        ROS_WARN("%s, use the default imu_topic name %s", this->node_name.c_str(), dist_pub_topic_name.c_str());
    }
    if (nh.hasParam("strength_topic"))
    {
        nh.getParam("strength_topic", strength_pub_topic_name);
        ROS_INFO("%s, use strength_topic name %s", this->node_name.c_str(), strength_pub_topic_name.c_str());
    }
    else
    {
        ROS_WARN("%s, use the default strength_topic name %s", this->node_name.c_str(), strength_pub_topic_name.c_str());
    }
    if (nh.hasParam("mode_topic"))
    {
        nh.getParam("mode_topic", mode_pub_topic_name);
        ROS_INFO("%s, use mode_topic name %s", this->node_name.c_str(), mode_pub_topic_name.c_str());
    }
    else
    {
        ROS_WARN("%s, use the default mode_topic name %s", this->node_name.c_str(), mode_pub_topic_name.c_str());
    }
    dist_pub = nh.advertise<std_msgs::Float32>(dist_pub_topic_name, 1);
    strength_pub = nh.advertise<std_msgs::Int32>(strength_pub_topic_name, 1);
    mode_pub = nh.advertise<std_msgs::Int8>(mode_pub_topic_name, 1);


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

            // TODO need to add the header and the stamped.
            this->msg_dist.data = this->que_tfmini_data_.front().dist;
            this->msg_strength.data = this->que_tfmini_data_.front().strength;
            this->msg_mode.data = this->que_tfmini_data_.front().mode;

            this->dist_pub.publish(this->msg_dist);
            this->strength_pub.publish(this->msg_strength);
            this->mode_pub.publish(this->msg_mode);

            this->que_tfmini_data_.pop();
        }
    }
}

