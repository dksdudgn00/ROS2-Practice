#include <rclcpp/rclcpp.hpp>
#include <sensor_msgs/msg/image.hpp>
#include <cv_bridge/cv_bridge.h>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>

class ImageSubscriber : public rclcpp::Node
{
public:
    ImageSubscriber() : Node("image_subscriber")
    {
        cv::namedWindow(OPENCV_WINDOW, cv::WINDOW_AUTOSIZE);
        subscription_ = this->create_subscription<sensor_msgs::msg::Image>(
            "camera/image",
            10,
            std::bind(&ImageSubscriber::image_callback, this, std::placeholders::_1)
        );
        RCLCPP::INFO(this->get_logger(),
                "Image Subscriber Node started, waiting for images on 'camera/image' topic");
    }

    ~ImageSubscriber()
    {
        cv::destroyWindow(OPENCV_WINDOW);
    }
private:
    void image_callback(const sensor_msgs::msg::Image::SharedPtr msg)
    {
        cv_bridge::CvImagePtr cv_ptr;

        try
        {
            cv_ptr = cv_bridge::toCvCopy(msg, msg->encoding);
        }
        catch (cv_bridge::Exception& e)
        {
            RCLCPP::ERROR(this->get_logger(), "cv_bridge exception: %s", e.what());
            return;
        }

        cv::circle(
            cv_ptr->image,
            cv::Point(cv_ptr->image.cols / 2, cv_ptr->image.rows / 2),
            20,
            CV_RGB(255, 0, 0),
            2
        );

        cv::imshow(OPENCV_WINDOW, cv_ptr->image);

        cv::waitKey(3);

        RCLCPP_INFO(this->get_logger(), "Received image. Time stamp: %f",
                    this->now().seconds());
    }

    rclcpp::Subscription<sensor_msgs::msg::Image>::SharedPtr subscription_;
    const std::string OPENCV_WINDOW = "Webcam Feed";


};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ImageSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}