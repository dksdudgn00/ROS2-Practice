
"""
ROS2 OpenCV Image Publisher
웹캠에서 영상을 읽어 ROS2 토픽(통신)으로 발생하는 노드
"""

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2

class ImagePublisher(Node):
    """
    ImagePublisher 클래스
    웹캠 영상을 캡쳐하여 ROS2 Image 메시지로 발행
    """

    def __init__(self):
        super().__init__('image_publisher')

        self.publisher_ = self.create_publisher(Image, 'video_frames', 10)

        timer_period = 0.1
        self.timer = self.create_timer(timer_period, self.timer_callback)

        
        # 0번은 기본 웹캠 장치를 의미
        self.cap = cv2.VideoCapture(0)
        
        if not self.cap.isOpened():
            self.get_logger().error("Failed to open camera device 0")
            raise RuntimeError("Cannot open camera")
        
        self.br = CvBridge()

        self.get_logger().info('Image Publisher Node Started')
    
    def timer_callback(self):
        '''
        타이머 콜백함수
        주기적으로 웹캠에서 프레임을 읽고 ROS 토픽으로 발행
        '''

        ret, frame = self.cap.read()

        if ret == True:
            # 핵심: OpenCV 이미지(frame)을 ROS 메시지로 변환하여 발행
            # cv2_to_imgmsg(): numpy array -> sensor_msgs/Image
            self.publisher_.publish(self.br.cv2_to_imgmsg(frame))
            self.get_logger().info('Publisher video frame')
        else:
            self.get_logger().warn("Failed to capture frame")
    
    def __del__(self):
        ''' 노드 소멸자: 웹캠 리소스 해제 '''
        if self.cap.isOpened():
            self.cap.release()
            self.get_logger().info('Camera released')

def main(args=None):
    rclpy.init(args=args)
    image_publisher = ImagePublisher()
    rclpy.spin(image_publisher)
    image_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()