# Servo and Motor Control with Arduino

This project controls a servo motor and a motor driver using Arduino. The program reads serial input commands to move the motors forward, backward, left, and right, as well as control the servo.

## Features
- Control servo motor opening and closing with specific angles.
- Control motor driver for forward, backward, left, and right movements.
- Adjust motor speed dynamically.
- Stop motor movement when needed.

## Components Used
- Arduino board
- Servo motor
- L298N motor driver
- DC motors
- Power supply

## Pin Configuration
| Component | Pin |
|-----------|-----|
| Servo Motor | 2 |
| Motor Driver Enable A | 5 |
| Motor Driver Enable B | 6 |
| Motor Driver Input 1 | 9 |
| Motor Driver Input 2 | 10 |
| Motor Driver Input 3 | 11 |
| Motor Driver Input 4 | 12 |

## Serial Commands
| Command | Function |
|---------|----------|
| `D` | Open Servo |
| `I` | Close Servo |
| `C` | Fully Open Gripper |
| `A` | Increase Speed |
| `Y` | Decrease Speed |
| `F` | Move Forward |
| `B` | Move Backward |
| `R` | Turn Left |
| `L` | Turn Right |
| `S` | Stop Movement |

## Installation
1. Clone the repository:
   ```bash
   git clone https://github.com/YOUR_USERNAME/YOUR_REPOSITORY.git
