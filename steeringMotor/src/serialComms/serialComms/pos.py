# This node communicates via serial communication with the arduino, simplex communication I think
# This node in particular tells the arduino to set the position
# Clamps the position to prevent overshoot, wouldn't want the steering motor going 5000 degrees lol 
#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from std_msgs.msg import Float32
import serial


class SteeringNode(Node):

    def __init__(self):
        super().__init__('steering_node')

        try:
            self.ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
            self.get_logger().info("Serial connected")
        except Exception as e:
            self.get_logger().error(f"Serial failed: {e}")
            exit()

        self.subscription = self.create_subscription(
            Float32,
            '/steering_cmd',
            self.steering_callback,
            10
        )

        #This is the maximum angle the steering motor will rotate
        #It means +-60 is the maximum the motor will rotate regardless of the command
        self.max_angle = 60.0  

    def steering_callback(self, msg):
        angle = msg.data

        # Clamp angle
        angle = max(min(angle, self.max_angle), -self.max_angle)

        cmd = f"P {angle}\n"
        self.ser.write(cmd.encode())

        self.get_logger().info(f"Sent angle: {angle}")


def main(args=None):
    rclpy.init(args=args)

    node = SteeringNode()

    rclpy.spin(node)

    node.destroy_node()
    rclpy.shutdown()