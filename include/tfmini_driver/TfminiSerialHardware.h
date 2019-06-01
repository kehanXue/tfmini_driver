#ifndef TFMINISERIALHARDWARE_H_
#define TFMINISERIALHARDWARE_H_

#include <cstdint>
#include <cstring>
#include <queue>
#include <tfmini_driver/BoostSerialCommunicator.h>

namespace vwpp
{
    class TfminiSerialHardware
    {
    public:
        // TfminiSerialHardware();
        TfminiSerialHardware(std::string model_, std::string port_, int baud_,
                             int msg_length_,
                             boost_serial_base::flow_control::type fc_type_ = boost_serial_base::flow_control::none, 
                             boost_serial_base::parity::type pa_type_ = boost_serial_base::parity::none, 
                             boost_serial_base::stop_bits::type st_type = boost_serial_base::stop_bits::one);
        virtual ~TfminiSerialHardware();


        struct Orientation
        {
        public:
            double w;
            double x;
            double y;
            double z;
        };

        struct Vector3f
        {
        public:
            float x;
            float y;
            float z;
        };
        
        typedef Vector3f AngularVelocity;
        typedef Vector3f LinearAcceleration;
        typedef Vector3f MagneticField; 

        struct TfminiData
        {
            Orientation q_;
            AngularVelocity av_;
            LinearAcceleration la_;
            MagneticField mf_;
        };

        std::queue<TfminiSerialHardware::TfminiData> readData();
        std::queue<TfminiData> que_tfmini_data;

    private:

        std::string model;
        std::string port;
        const int baud;
        const int msg_length;

        boost_serial_base::flow_control::type fc_type;
        boost_serial_base::parity::type pa_type;
        boost_serial_base::stop_bits::type st_type;

        BoostSerialCommunicator* boost_serial_communicator;

        const uint8_t* msg_stop;
        const uint8_t* msg_start;

    };

} // namespace vwpp

#endif
