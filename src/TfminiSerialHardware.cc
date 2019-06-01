#include <utility>

#include <utility>

#include <tfmini_driver/TfminiSerialHardware.h>
#include <tfmini_driver/utils.h>
#include <eigen3/Eigen/Geometry> 
#include <iostream>

using namespace vwpp;

TfminiSerialHardware::TfminiSerialHardware(std::string model_, std::string port_, int baud_,
                                           int msg_length_,
                                           boost_serial_base::flow_control::type fc_type_,
                                           boost_serial_base::parity::type pa_type_, 
                                           boost_serial_base::stop_bits::type st_type_):
    model(std::move(model_)),
    port(std::move(port_)),
    baud(baud_),
    msg_length(msg_length_),
    fc_type(fc_type_),
    pa_type(pa_type_),
    st_type(st_type_)
{

    this->boost_serial_communicator = new BoostSerialCommunicator(this->port, this->baud);

    if(model == "tfmini")
    {
        // TODO
        usleep(1000 * 1000);
    }

    std::cout << "\033[32m" << "Start streaming data..."
              << "\033[0m" << std::endl;

}

TfminiSerialHardware::~TfminiSerialHardware()
{
    delete   this->boost_serial_communicator;
}

std::queue<TfminiSerialHardware::TfminiData> TfminiSerialHardware::readData()
{
    static uint8_t* data_raw;

    data_raw = boost_serial_communicator->getMessage(this->msg_length);

    // When get the new data_raw, clean up the queue buf before.
    while ( !(this->que_tfmini_data.empty()) )
    {
        this->que_tfmini_data.pop();
    }

    const int msg_buf_length = 2*(this->msg_length);
    for (int header_index = 0; header_index < (msg_buf_length - 1); ++header_index)
    {
        if(model == "tfmini" && data_raw[header_index] == 0x59 && data_raw[header_index + 1] == 0x59)
        {
            // When the data queue get errors.
            if (boost_serial_communicator->fixError(header_index, this->msg_length) == -1)
            {
                // continue;
                break;
            }


            unsigned char *data = data_raw + header_index;
            uint8_t data_length = 9;


            uint32_t checksum = 0;
            for(int i = 0; i < data_length - 1  ; ++i)
            {
                checksum += (uint32_t) data[i];
            }

            uint16_t check = checksum % 256;
            uint16_t check_true = data[data_length-1];

            if (check != check_true)
            {
                std::cout << "check error" << std::endl;
                continue;
            }


            TfminiData per_tfmini_data{};
            per_tfmini_data.dist = d2f_dist(data + 2);
            per_tfmini_data.strength = d2i_strength(data + 4);
            per_tfmini_data.mode = u82i_mode(data + 6);

            this->que_tfmini_data.push(per_tfmini_data);
        }

    }

    delete[] data_raw;

    return (this->que_tfmini_data);
}

