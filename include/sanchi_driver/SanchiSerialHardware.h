#ifndef SANCHISERIALHARDWARE_H_
#define SANCHISERIALHARDWARE_H_

#include <cstdint>
#include <cstring>
#include <queue>
#include <sanchi_driver/BoostSerialCommunicator.h>

namespace vwpp
{
    class SanchiSerialHardware
    {
    public:
        // SanchiSerialHardware();
        SanchiSerialHardware(std::string model_, std::string port_, int baud_, 
                             int msg_length_,
                             boost_serial_base::flow_control::type fc_type_ = boost_serial_base::flow_control::none, 
                             boost_serial_base::parity::type pa_type_ = boost_serial_base::parity::none, 
                             boost_serial_base::stop_bits::type st_type = boost_serial_base::stop_bits::one);
        virtual ~SanchiSerialHardware();


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

        struct SanchiData
        {
            Orientation q_;
            AngularVelocity av_;
            LinearAcceleration la_;
            MagneticField mf_;
        };

        std::queue<SanchiSerialHardware::SanchiData> readData(); 
        std::queue<SanchiData> que_sanchi_data;        

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
