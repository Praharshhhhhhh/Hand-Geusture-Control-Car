# Hand Gesture Controlled 4WD Car using Arduino + ADXL345 + NRF24L01

##  Overview

This project is a **Hand Gesture Controlled 4 Wheel Drive Robot Car** built using:

* Arduino UNO
* ADXL345 Accelerometer Sensor
* NRF24L01 Wireless Transceiver Modules
* L298N Motor Driver
* BO Motors (4WD)

The car is controlled by tilting your hand.
The transmitter reads hand movement using the ADXL345 accelerometer and wirelessly sends commands to the receiver mounted on the car.

---

#  Features

* Hand gesture controlled movement
* Wireless control using NRF24L01
* Smooth acceleration and deceleration
* Forward / Backward / Left / Right movement
* 4 Wheel Drive support
* Adjustable speed using tilt angle
* Long range wireless communication
* Stable and responsive control

---

#  Working Principle

## Transmitter Side

1. ADXL345 detects hand tilt.
2. Arduino processes tilt direction.
3. Speed is calculated proportionally.
4. Data is transmitted wirelessly using NRF24L01.

## Receiver Side

1. NRF24L01 receives movement commands.
2. Arduino processes received data.
3. L298N drives motors accordingly.
4. Car moves based on hand gestures.

---

# 🛠 Components Required

| Component             | Quantity |
| --------------------- | -------- |
| Arduino UNO/Nano      | 2        |
| NRF24L01 Module       | 2        |
| ADXL345 Accelerometer | 1        |
| L298N Motor Driver    | 1        |
| BO Motors             | 4        |
| Wheels                | 4        |
| 18650 Batteries       | 2 or 3   |
| Battery Holder        | 1        |
| Jumper Wires          | Several  |
| Chassis               | 1        |
| Breadboard (optional) | 1        |
| 10µF Capacitor        | 1        |

---

# 🛒 Buying Links

## Arduino UNO

[https://robu.in/product/arduino-uno-r3-board-atmega328p/](https://robu.in/product/arduino-uno-r3-board-atmega328p/)

## NRF24L01

[https://robu.in/product/nrf24l01-2-4ghz-wireless-transceiver-module/](https://robu.in/product/nrf24l01-2-4ghz-wireless-transceiver-module/)

## ADXL345

[https://robu.in/product/adxl345-3-axis-digital-acceleration-gravity-tilt-module/](https://robu.in/product/adxl345-3-axis-digital-acceleration-gravity-tilt-module/)

## L298N Motor Driver

[https://robu.in/product/l298-based-motor-driver-module/](https://robu.in/product/l298-based-motor-driver-module/)

## BO Motors

[https://robu.in/product/100-rpm-single-shaft-bo-motor-straight/](https://robu.in/product/100-rpm-single-shaft-bo-motor-straight/)

## Robot Chassis

[https://robu.in/product/4wd-smart-robot-car-chassis-kit/](https://robu.in/product/4wd-smart-robot-car-chassis-kit/)

## 18650 Battery Holder

[https://robu.in/product/2x18650-battery-holder/](https://robu.in/product/2x18650-battery-holder/)

## 18650 Cells

[https://robu.in/product/samsung-18650-li-ion-battery/](https://robu.in/product/samsung-18650-li-ion-battery/)

---

# 🔌 Receiver Side Connections

## NRF24L01 ↔ Arduino UNO

| NRF24L01 | Arduino UNO   |
| -------- | ------------- |
| VCC      | 3.3V          |
| GND      | GND           |
| CE       | D2            |
| CSN      | D3            |
| SCK      | D13           |
| MOSI     | D11           |
| MISO     | D12           |
| IRQ      | Not Connected |

---

## L298N ↔ Arduino UNO

| L298N | Arduino UNO |
| ----- | ----------- |
| ENA   | D6          |
| IN1   | D4          |
| IN2   | D5          |
| IN3   | D7          |
| IN4   | D9          |
| ENB   | D10         |

---

## Motors ↔ L298N

| Motor       | L298N Output |
| ----------- | ------------ |
| Front Left  | OUT1         |
| Front Right | OUT2         |
| Rear Left   | OUT3         |
| Rear Right  | OUT4         |

---

# 🔌 Transmitter Side Connections

## ADXL345 ↔ Arduino UNO

| ADXL345 | Arduino UNO   |
| ------- | ------------- |
| VCC     | 3.3V          |
| GND     | GND           |
| SDA     | A4            |
| SCL     | A5            |
| CS      | 3.3V          |
| SDO     | GND           |
| INT1    | Not Connected |
| INT2    | Not Connected |

---

## NRF24L01 ↔ Arduino UNO

| NRF24L01 | Arduino UNO   |
| -------- | ------------- |
| VCC      | 3.3V          |
| GND      | GND           |
| CE       | D7            |
| CSN      | D8            |
| SCK      | D13           |
| MOSI     | D11           |
| MISO     | D12           |
| IRQ      | Not Connected |

---

# ⚠ Important Notes

## NRF24L01 Stability

Add a 10µF capacitor between:

* VCC
* GND

close to the NRF24L01 module.

This prevents:

* packet loss
* random disconnects
* unstable movement

---

## Power Supply

* Use separate power for motors.
* Do NOT power motors from Arduino 5V.
* Use 7V–12V battery pack for L298N.

---

# Required Arduino Libraries

Install these from Arduino Library Manager:

* RF24
* Adafruit ADXL345
* Adafruit Unified Sensor

---

#  Installation Steps

## Step 1

Install Arduino IDE.

## Step 2

Install required libraries.

## Step 3

Upload transmitter code to transmitter Arduino.

## Step 4

Upload receiver code to receiver Arduino.

## Step 5

Connect all components according to wiring diagram.

## Step 6

Power ON both systems.

## Step 7

Tilt your hand to control the robot.

---

#  Gesture Controls

| Hand Gesture  | Car Movement  |
| ------------- | ------------- |
| Tilt Forward  | Move Forward  |
| Tilt Backward | Move Backward |
| Tilt Left     | Turn Left     |
| Tilt Right    | Turn Right    |
| Flat Hand     | Stop          |

---

#  Project Structure

```text
Hand-Gesture-Control-Car/
│
├── transmitter/
│   └── transmitter.ino
│   └── transmitter_connection.png
│
├── receiver/
│   └── receiver.ino
|   └── receiver_connection.png
└── README.md
```

---

#  Future Improvements

* PID based steering
* Better gesture filtering
* Gyroscope integration
* OLED display
* Bluetooth control mode
* Camera streaming
* Obstacle avoidance
* Autonomous navigation

---

#  Troubleshooting

## NRF24L01 Not Working

* Check 3.3V supply
* Add capacitor
* Verify CE and CSN pins
* Check wiring carefully

---

## Car Moves Randomly

* Calibrate ADXL345
* Add dead zone in code
* Tighten power connections

---

## Motors Not Rotating

* Check battery voltage
* Verify L298N connections
* Ensure ENA and ENB are connected

---

# 📸 Project Demo Ideas

You can showcase:

* Hand gesture driving
* Obstacle course
* Speed control demo
* Gesture responsiveness
* Wireless range test

---

#  Credits

Developed using:

* Arduino Platform
* NRF24L01 RF Communication
* ADXL345 Motion Sensing
* L298N Motor Control

---

# 📜 License

This project is open-source and free to use for educationa
