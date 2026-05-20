#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <libserial/SerialPort.h>
#include <string>
#include <chrono>
#include <memory>

using namespace LibSerial;
using namespace std::chrono_literals;

class SerialReaderNode : public rclcpp::Node
{
public:
    SerialReaderNode() : Node("serial_reader_node")
    {
        // 파라미터 선언 (기본값 설정)
        this->declare_parameter<std::string>("serial_port", "/dev/ttyUSB0");
        this->declare_parameter<int>("baud_rate", 115200);
        
        std::string port_name = this->get_parameter("serial_port").as_string();
        int baud_rate = this->get_parameter("baud_rate").as_int();

        // 'arduino_data' 토픽 퍼블리셔 생성
        publisher_ = this->create_publisher<std::msgs::msg::String>("arduino_data", 10);

        // 시리얼 포트 오픈 및 설정
        try
        {
            serial_port_.Open(port_name);
            BaudRate serial_baud_rate;
            switch(baud_rate)
            {
                case 115200: serial_baud_rate = BaudRate::BAUD_115200; break;
                default: serial_baud_rate = BaudRate::BAUD_9600; break;
            }

            serial_port_.SetBaudRate(serial_baud_rate);

            RCLCPP_INFO(this->get_logger(), "Serial port %s opened successfully", port_name.c_str());

        }
        catch (const OpenFailed& e)
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to opne port: %s", e.what());
            return;
        }

        timer_ = this->create_wall_timer(
            10ms, std::bind(&SerialReaderNode::read_serial_data, this)
        );

    }
private:
    void read_serial_data()
    {
        if (!serial_port_.IsOpen()) return;
        try
        {
            if (serial_port_.IsDataAvailable())
            {
                std::string received_data;
                serial_port_.ReadLine(received_data, '\n', 1000);

                if (!received_data.empty())
                {
                    auto message = std_msgs::msg::String();
                    message.data = received_data;
                    publisher_->publish(message);
                }
            }

        }
        catch(const std::exception& e)
        {
            RCLCPP_ERROR(this->get_logger(), "Error:%s", e.What());
        }

    }

    SerialPort serial_port_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SerialReaderNode>());
    rclcpp::shutdown();
    return 0;
}