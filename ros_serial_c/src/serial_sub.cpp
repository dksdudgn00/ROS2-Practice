#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <memory>
#include <functional>

using std::placeholders::_1;

class SerialSubscriberNode : public rclcpp::Node
{
public:
    SerialSubscriberNode() : Node("serial_subscriber_node")
    {
        // 'arduino_data' 토픽 구독 설정
        subscriber_ = this->create_subscription<std_msgs::msg::String>(
            "arduino_data",
            10,
            std::bind(&SerialSubscriberNode::topic_callback, this, _1)
        );
        RCLCPP_INFO(this->get_logger(), "Serial Subscriber Node started");
    }

private:
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
    {
        RCLCPP_INFO(this->get_logger(), "I heard: '%s'", msg->data.c_str());
    }
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc,argv);
    rclcpp::spin(std::make_shared<SerialSubscriberNode>());
    rclcpp::shutdown();
    return 0;
    
}