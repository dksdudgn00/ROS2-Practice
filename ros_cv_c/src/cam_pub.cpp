#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/gighgui.hpp>

using namespace std::chrono_literals;

class WebcamPublisher : public rclcpp::Node
{
public:
    WebcamPublisher() : Node("webcam_publisher"), count_(0)
    {
        cap_.open(0)
        if (!cap_.isOpened())
        {
            RCLCPP_ERROR(this->get_logger(), "Error: Could not open camera");
            rclcpp.shutdown();
            return;
        }

        publisher_ = this->create_publisher<sensor_msgs::msgs::msg::Image>("camera/image",
        10);

        timer_ = this->create_wall_timer(
            50ms,
            std::bind(&WebcamPublisher::timer_callback, this)
        );

        RCLCPP_INFO(this->get_logger(), "Webcam Publisher Node started.");
    }

private:
    void timer_callback()
    {
        cv::Mat frame;
        cap_ >> frame;

        if (frame.empty())
        {
            RCLCPP_WARN(this->get_logger(), "Warning: Captured empty frame.");
            return;
        }

        std_msgs::msg::Header header;
        header.stamp = this->now();
        header.frame_id = "camera_frame";

        auto msg = cv_bridge::CvImage(header, "bgr8", frame).toImageMsg();

        publisher_->publish(*msg)
        RCLCPP_INFO(this->get_logger(), "Image frame %zu published.", count_++);
    }

    cv::VideoCapture cap_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<sensor_msgs::msg::Image>::SharedPtr publisher_;
    size_t count_;
}

int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<WebcamPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}