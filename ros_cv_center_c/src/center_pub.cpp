#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cv2_msg/msg/msg_center.h>

using namespace std::chrono_literals;

class ColorDetectorNode : public rclcpp::Node
{
public:
    ColorDetectorNode() : Node("color_detector_node")
    {
        this->declare_parameter("camera_index", 0);
        int camera_index = this->get_parameter("camera_index").as_int();

        cap_.open(camera_index);
        if (!cap_.isOpened())
        {
            RCLCPP_ERROR(this->get_logger(), "Failed to open camera device %d", camera_index);
            rclcpp::shutdown();
            return;
        }

        publisher_ = this->create_publisher<cv2_msg::msg::MsgCenter>("red_center", 10);

        timer_ = this->create_wall_timer(
            33ms,
            std::bind(&ColorDetectorNode::timer_callback, this)
        );

        RCLCPP_INFO(this->get_logger(), "Color Detector Node started.");
    }

    ~ColorDetectorNode()
    {
        cv::destroyAllWindows();
        if (cap_.isOpened())
        {
            cap_.release();
        }
    }

private:
    void timer_callback()
    {
        cv::Mat frame;
        cap_ >> frame;

        if (frame.empty())
        {
            RCLCPP_WARN(this->get_logger(), "Captured empty frame.");
            return;
        }

        auto [cx, cy] = find_red_object_center(frame);

        auto center_msg = cv2_msg::msg::MsgCenter();
        center_msg.x = cx;
        center_msg.y = cy;
        publisher_->publish(center_msg);

        RCLCPP_INFO(this->get_logger(), "Publishing center: (%ld, %ld)", cx, cy);

        cv::imshow("Original Frame", frame);
        cv::WaitKey(1);
    }

    std::pair<int64_t, int64_t> find_red_object_center(cv::Mat& frame)
    {
        int64_t cx = 0, cy = 0;

        // 1.BGR -> HSV
        cv::Mat hsv_frame;
        cv::cvtColor(frame, hsv_frame, cv::COLOR_BGR2HSV);

        // 2. 빨간색 범위 마스크 생성
        cv::Mat mask1, mask2, red_mask;
        cv::inRange(hsv_frame, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255), mask1);
        cv::inRange(hsv_frame, cv::Scalar(170, 100, 100), cv::Scalar(180,255,255), mask2);

        // 두 마스크 합치기 
        cv::addWeighted(mask1, 1.0, mask2, 1.0, 0.0, red_mask);

        // 3. 노이즈 제거 (모폴로지 연산)
        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5,5));
        cv::morphologyEx(red_mask, red_mask, cv::MORPH_OPEN, kernel);
        cv::morphologyEx(red_mask, red_mask, cv::MORPH_CLOSE, kernel);

        std::vector<std::vector<cv::Point>> contours;
        cv::findContours(red_mask, contours, cv::RETR_EXTERNAL, cv::CHAIN__APPROX_SIMPLE);

        if (!contours.empty())
        {
            auto largest_contour = *std::max_element(
                contours.begin(), contours.end(),
                [](const std::vector<cv::Point>& c1, const std::vector<cv::Point>& c2)
                {
                    return cv::contourArea(c1) < cv::contourArea(c2);
                });
            
                cv::Moments m = cv::moments(largest_contour);

                if (m.m00 > 0)
                {
                    cx = static_cast<int64_t>(m.m10 / m.m00);
                    cy = static_cast<int64_t>(m.m01 / m.m00);

                    cv::drawContours(frame, std::vector<std::vector<cv::Point>>{largest_contour}, 
                                 -1, cv::Scalar(0, 255, 0), 2);

                    // 중심점에 빨간색 원 그리기
                    cv::circle(frame, cv::Point(cx, cy), 5, cv::Scalar(0, 0, 255), -1);
                }
        }

        cv::imshow("Red Mask", red_mask);

        return {cx, cy};
    }

    cv::VideoCapture cap_;
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<cv2_msg::msg::MsgCenter>::SharedPtr publisher_;
};


int main(int argc, char* argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ColorDetectorNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}