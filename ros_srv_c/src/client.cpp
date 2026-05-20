#include <rclcpp/rclcpp.hpp>
#include "cv_msg/srv/srv_addint.hpp"
#include <memory>
#include <cstdlib>
#include <chrono>

using namespace std::chrono_literals;

class AddIntsClient : public rclcpp::Node
{
public:
    AddIntsClient(int64_t a, int64_t b) : Node("add_two_ints_client")
    {
        client_ = this->create_client<cv_msg::srv::SrvAddint>("add_two_ints");
        RCLCPP_INFO(this->get_logger(), "Client Node created.");
        a_ = a;
        b_ = b;
    }

    void send_request()
    {
        while (!client_->wait_for_service(1s))
        {
            if (!rclcpp::ok())
            {
                RCLCPP_ERROR(this->get_logger(), "Interrupted. Exiting.");
                return;
            }
            RCLCPP_INFO(this->get_logger(), "Service not available yet, wating...");
        }

        auto request = std::make_shared<cv_msg::srv::SrvAddint::Request>();
        request->a = a_;
        request->b = b_;
        
        auto result_future = client_->async_send_request(request);

        if (rclcpp::spin_until_future_complete(this->get_node_base_interface(), result_future)
            == rclcpp::FutureReturnCode::SUCCESS)
        {
            auto response = result_future.get();
            RCLCPP_INFO(this->get_logger(),
                        "Received response: %ld + %ld = %ld",
                        a_, b_, response->sum);
        }
        else
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to call service.");
        }
    }
private:
    rclcpp::Client<cv_msg::srv::SrvAddint>::SharedPtr client_;
    int64_t a_;
    int64_t b_;
};

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);

    if (argc != 3)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Usage: add_two_ints_client XY");
        return 1;
    }

    auto client_node = std::make_shared<AddIntsClient>(atoll(argv[1]),
        atoll(argv[2]));
    client_node->send_request();
    rclcpp::shutdown();
    return 0;
}