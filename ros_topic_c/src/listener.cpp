#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <memory>

class HelloWorldSubscriber : public rclcpp::Node
{
public:
    HelloWorldSubscriber() : Node("hello_world_subscriber")
    {
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "hello_world_topic",
            10,
            std::bind(&HelloWorldSubscriber::topic_callback, this,
            std::placeholders::_1)
        );

        RCLCPP_INFO(this->get_logger(), "Hello World Subscriber 노드가 시적되었습니다.");
        RCLCPP_INFO(this->get_logger(), "hello_world_topic 토픽을 구독하고 있습니다.");
    }

private:
    void topic_callback(const std_msgs::msg::String::SharedPtr msg) const
    {
        RCLCPP_INFO(this->get_logger(), "수신된 메시지: '%s'", msg->data.c_str());
    }

    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<HelloWorldSubscriber>();

    RCLCPP_INFO(node->get_logger(), "Hello World Subscriber를 시작합니다...");
    RCLCPP_INFO(node->get_logger(), "메시지를 기다리는 중... (Ctrl+C로 종료)");

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;
}