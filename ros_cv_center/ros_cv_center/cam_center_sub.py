import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
from cv2_msg.msg import MsgCenter

class ImageSubscriber(Node):
    def __init__(self):
        super().__init__('image_subscriber')

        self.subscription_img = self.create_subscription(
            Image,
            'video_frames',
            self.listener_callback_img,
            10
        )

        self.subscription_xy = self.create_subscription(
            MsgCenter,
            'red_center',
            self.listener_callback_xy,
            10
        )
        self.br = CvBridge()

    def listener_callback_xy(self, data):
        self.get_logger().info('Receiving video frame')
        current_frame = self.br.imgmsg_to_cv2(data)
        cv2.imshow("camera", current_frame)
        cv2.waitKey(1)

    def listener_callback_xy(self, data):
        """중심점 좌표 수신 콜백"""
        self.get_logger().info(f'Red center: ({data.x}, {data.y})')

def main(args=None):
    rclpy.init(args=args)
    image_subscriber = ImageSubscriber()
    rclpy.spin(image_subscriber)
    image_subscriber.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()