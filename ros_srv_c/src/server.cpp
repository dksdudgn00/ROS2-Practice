#include <rclcpp/rclcpp.hpp>
#include "cv_msg/srv/srv_addint.hpp"
#include <memory>
#include <functional>

using SrvAddint = cv_msg::srv::SrvAddint;

void add(const std::shared_ptr<SrvAddint::Request> request,
        const std::shared_ptr<SrvAddint::Response> response)
{
    response->sum = request->a + request->b;

    RCLCPP_INFO(rclcpp::get_logger("add_two_ints_server"),
            "incoming request: a = %ld, b = %ld",
            request->a, request->b);
    RCLCPP_INFO(rclcpp::get_logger("add_two_ints_server"),
            "Sending back response: sum = %ld",
            response->sum);
}

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);

    std::shared_ptr<rclcpp::Node> node = 
        std::make_shared<rclcpp::Node>("add_two_ints_server");
    
    // 서비스 서버 생성: 타입, 서비스명, 콜백함수 바인딩
    rclcpp::Service<SrvAddint>::SharedPtr service = 
        node->create_service<SrvAddint>("add_two_ints", &add);
    
    RCLCPP_INFO(node->get_logger(), "Ready to add two ints.");

    rclcpp::spin(node);
    rclcpp::shutdown();

    return 0;

}
