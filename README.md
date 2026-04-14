# CAN/ROS/Arduino Project

## Overview
This project integrates CAN (Controller Area Network), ROS (Robot Operating System), and Arduino to create a robust communication system for embedded applications. It serves as a bridge between hardware interfaces and higher-level software abstractions. The repo currently only contains how to control the steering motor AK60-39 Cubemars via CAN control loop 6 (Position+Velocity+Acceleration Control Loop)

## Key Features
- **CAN Communication**: Efficient communication between microcontrollers and devices in a network.
- **ROS Integration**: Utilizing ROS for protocol and message handling, allowing for advanced robotics development.
- **Arduino Control**: Leveraging the Arduino platform for easy prototyping and hardware interaction.

## Components
1. **Arduino Board**: Acts as the primary controller and interface with the CAN bus.
2. **CAN Transceiver**: Facilitates CAN communications.
3. **ROS Nodes**: Handle the processing and transmission of messages through ROS topics.
4. **Sensors & Actuators**: Connected to the Arduino for data collection and control.

## Setup Instructions
1. **Hardware Setup**: Connect the CAN transceiver to the Arduino and peripherals as per the schematics provided.
2. **Software Installation**: Install the necessary libraries for Arduino and ROS on your respective development environments.
3. **Configuration**: Configure the CAN bus settings, ROS parameters, and initialize the nodes.
4. **Execution**: Run the ROS nodes and monitor the system.

## Usage

  - Go to your desired folder
    
```
git clone https://github.com/tanvayGupta/mrControls.git
cd mrControls
colcon build
source install/setup.bash
```

 - After doing this you should do ros2 topic echo, and check whether a ```/steer``` topic is visible
If it is, go ahead and enjoy... FYI /steer takes in msgType ```Ackermann_msgs/msg/AckermannDriveStamped```

In case dependencies fail, run this in ```./mrControls```
```
rosdep install --from-paths src --ignore-src -y -r
```
If it still fails, you'll figure it out trust me

- Yippee, now its ready to use
- Incase you don't have publisher node ready

```ros2 topic pub /steering_cmd std_msgs/Float32 "{data: 20.0}"``` 

should do the trick. Also, data:20.0 will set the angle at 20 degrees. It is clamped in the node, to +-60, so using values above it wont work unless you go change that



- The repo only contains controlling by position, for AK60-39 Steering Motor
- Uses Position+Velocity Control Loop
  

## Conclusion
This project provides a highly flexible and scalable solution for integrating CAN systems with ROS and Arduino, making it suitable for various applications in robotics and automation.

## Pin connections
MCP2515	Arduino UNO Pin	Purpose
- VCC	    5V          Power
- GND	    GND         Common ground
- CS	    D10	        Chip Select
- SCK	    D13	        SPI Clock
- MOSI    D11	        Data → MCP2515
- MISO	  D12	        Data → Arduino
- INT	    D2          (optional)


