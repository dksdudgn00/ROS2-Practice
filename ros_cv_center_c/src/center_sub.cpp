#include <rclcpp/rclcpp.hpp>
#include <cv2_msg/msg/msg_center.hpp>

class CenterPointSubscriberNode : public rclcpp::Node
{
public:
    CenterPointSubscriberNode() : Node("center_point_subscriber_node")
    {
        subscription_ = this->create_subscription<cv2_msg::msg::MsgCenter>(
            "red_center",
            10,
            std::bind(&CenterPointSubscriberNode::center_callback, this, std::placeholders::_1));
     
        RCLCPP::INFO(this->get_logger(),
            "Center Point Subscriber Node started, waiting for messages on 'red_center' topic");
    }
private:
    void center_callback(const cv2_msg::msg::MsgCenter::SharedPtr msg)
    {
        if (msg->x == 0 && msg->y == 0)
        {
            RCLCPP_INFO(this->get_logger(), "No red object detected.");
        }
        else
        {
            RCLCPP_INFO(this->get_logger(), "Center Point Detected: (X: %ld, Y: %ld)",
                        msg->x, msg->y);
        }
    }

    rclcpp::Subscription<cv2_msg::msg::MsgCenter>::SharedPtr subscription_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<CenterPointSubscriberNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}