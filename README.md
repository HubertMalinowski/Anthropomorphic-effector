# Anthropomorphic effector in the shape of a human hand based on the MQTT protocol

## Overview

This project represents my engineering thesis, aimed at developing a comprehensive system that encompasses both the mechanical construction of a robotic hand and the controlling software. The operator's hand movements are captured by a webcam, and through the utilization of tools such as OpenCV, the state of the fingers (extended or bent) is determined. This information is then transmitted to the effector using the MQTT protocol, enabling precise replication of human hand movements by the robotic counterpart. 

## Features

- **Design**: The hand was conceived and crafted with a cyberpunk aesthetic in mind, blending futuristic innovation with a gritty, high-tech edge.
- **MQTT Protocol for Communication**: The project employs MQTT (Message Queuing Telemetry Transport) for efficient and reliable communication between the control system and the hand, ensuring real-time responsiveness.
- **3D Printed Components**: Leveraging the flexibility and accessibility of 3D printing technology, the hand's components are designed for customization and rapid prototyping, allowing for easy modifications and improvements.
- **Open-Source Software**: The control algorithms and software interfaces are open-source, encouraging community contributions, experimentation, and widespread adoption.

## Applications

- **Educational Tool**: Serving as a practical example of cutting-edge robotics, the project can be used in educational settings to teach engineering, robotics, and computer science principles.
- **Research in Human-Robot Interaction**: The anthropomorphic design and advanced control system make the mechanical hand an ideal platform for studying and developing new human-robot interaction paradigms.

## Technical Specifications

- **Actuators**: SG90 servos for finger movements, offering a balance between torque, speed, and precision.
- **Materials**: Primarily constructed from PLA (Polylactic Acid) due to its biodegradability, strength, and ease of use in 3D printing.
- **Control Hardware**: Utilizes ESP32 module for WiFi connectivity and servos control.
- **Software**: Custom-developed algorithms for gesture recognition and hand movement control, available on GitHub for community use and contribution.
