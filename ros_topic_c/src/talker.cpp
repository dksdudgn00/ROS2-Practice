#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <chrono>
#include <memory>
#include <string>

using namespace std::chrono_literals;

class HelloWorldPublisher : public rclcpp::Node
{
public:
    HelloWorldPublisher() : Node("Hello_world_publisher")
    {
        count_ = 0;
        publisher_ = this->create_publisher<std_msgs::msg::String>("hello_world_topic", 10);
        timer_ = this->create_wall_timer(
            500ms,
            std::bind(&HelloWorldPublisher::timer_callback, this)
        );

        RCLCPP_INFO(this->get_logger(), "Hello World Publisher 노드가 시작되었습니다.");
    }


private:
    void timer_callback()
    {
        auto message = std_msgs::msg::String();

        message.data = "Hello World" + std::to_string(count_++);

        publisher_->publish(message);

        RCLCPP_INFO(this->get_logger(), "발행된 메시지: '%s'", message.data.c_str());
    }

    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    size_t count_;

};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);

    auto node = std::make_shared<HelloWorldPublisher>();

    RCLCPP_INFO(node->get_logger(), "Hello Wolrd Publisher를 시작합니다...");
    
    // 노드 실행 (블로킹)
    rclcpp::spin(node);
    
    rclcpp::shutdown();

    return 0;
}