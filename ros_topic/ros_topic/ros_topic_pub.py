import rclpy
from rclpy.node import Node
from std_msgs.msg import String

class MinimalPublisher(Node):
    
    def __init__(self):
        super().__init__("minimal_publisher")
        # 퍼블리셔 생성: (메시지 타입, 토픽 이름, 큐 사이즈)
        self.publisher_ = self.create_publisher(String, "topic_py", 10)
        timer_period = 0.5 # seconds (0.5초마다 발행)
        self.timer = self.create_timer(timer_period, self.timer_callback)
        self.i = 0

    def timer_callback(self):
        msg = String()
        msg.data = "Hello World: %d" % self.i
        self.publisher_.publish(msg)
        self.get_logger().info('Publishing: "%s"' % msg.data)
        self.i += 1

    
def main(args=None):
    rclpy.init(args=args)

    minimal_publisher = MinimalPublisher()
    rclpy.spin(minimal_publisher)

    # 노드 종료 처리
    minimal_publisher.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()