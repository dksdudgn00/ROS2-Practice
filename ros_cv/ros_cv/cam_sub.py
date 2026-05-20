'''
ROS2 OpenCCV Image Subscriber
ROS2 토픽으로 발행된 영상을 수신, 화면에 표시
'''

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2

class ImageSubscriber(Node):
    """
    ImageSubscriber Class
    ROS2 Image 메시지를 구독하여 OpenCV 창에 표시
    """

    def __init__(self):
        super().__init__('image_subscriber')

        self.subscription = self.create_subscription(
            Image,
            'video_frames',
            self.listener_callback,
            10
        )

        self.subscription
        self.br = CvBridge()
        self.get_logger().info('Image Subscriber Node Started')
    
    def listener_callback(self, data):
        self.get_logger().info('Receiving video frame')
        current_frame = self.br.imgmsg_to_cv2(data)
        cv2.imshow('camera', current_frame)
        cv2.waitKey(1)

def main(args=None):
    rclpy.init(args=args)
    image_subscriber = ImageSubscriber()

    try:
        rclpy.spin(image_subscriber)
    except KeyboardInterrupt:
        pass
    finally:
        cv2.destroyAllWindows()
        image_subscriber.destroy_node()
        rclpy.shutdown()

        
if __name__ == '__main__':
    main()