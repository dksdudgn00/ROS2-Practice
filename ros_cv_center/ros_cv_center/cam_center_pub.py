import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
import numpy as np
from cv_msg.msg import MsgCenter

class ImagePublisher(Node):
    def __init__(self):
        super().__init__('image_publisher')

        self.publisher_img = self.create_publisher(Image, 'vidoe_frames', 10)
        self.publisher_xy = self.create_publisher(MsgCenter, 'red_center', 10)

        timer_period = 0.1
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.cap = cv2.VideoCapture(0)
        self.br = CvBridge()
        self.cx = 0
        self.cy = 0
    
    def timer_callback(self):
        ret, frame = self.cap.read()

        if ret == True:

            frame, self.cx, self.cy = self.find_and_mark_red_object(frame)

            cv2.imshow('red', frame)
            cv2.waitKey(1)

            self.publisher_img.publish(self.br.cv2_to_imgmsg(frame))

            msg = MsgCenter()
            msg.x = self.cx
            msg.y = self.cy
            self.publisher_xy.publish(msg)

            self.get_logger().info(f'Publishing: ({self.cx}, {self.cy})')

    def find_and_mark_red_object(self, img):
        cx, cy = 0, 0
        hsv = cv2.cvtColor(img, cv2.COLOR_BGR2HSV)
        lower_red = np.array([0,120,70])
        upper_red = np.array([10,255,255])
        mask = cv2.inRange(hsv, lower_red, upper_red)
        contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL,
                                        cv2.CHAIN_APPROX_SIMPLE)
        if len(contours) > 0:
            largest_contour = max(contours, key=cv2.contourArea)

            M = cv2.moments(largest_contour)

            if M["m00"] != 0:
                cx = int(M["m10"] / M["m00"])
                cy = int(M["m01"] / M['m00'])

                cv2.circle(img, (cx, cy), 5, (0,0,255), -1)
        return img, cx, cy
    
def main(args=None):
    rclpy.init(args=args)
    image_publisher = ImagePublisher()
    rclpy.spin(image_publisher)
    image_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()