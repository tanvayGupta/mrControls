# CAN/ROS/Arduino Project

## Overview
This project integrates CAN (Controller Area Network), ROS (Robot Operating System), and Arduino to create a robust communication system for embedded applications. It serves as a bridge between hardware interfaces and higher-level software abstractions.

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

## Usage Examples
- Sending sensor data through the CAN bus to ROS.
- Commanding motors via ROS messages based on CAN input.

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
