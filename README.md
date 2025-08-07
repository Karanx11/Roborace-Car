# 🚗 RoboRace: ESP32 Bluetooth-Controlled Racing Car

This is a **Bluetooth-controlled RoboRace car** powered by an **ESP32 microcontroller** and driven by **300 RPM gear motors**. The car is controlled through an Android smartphone using a custom-built MIT App Inventor application that sends directional commands over Bluetooth.

---

## ⚙️ Features

- 🔧 **ESP32-based control**
- 📱 **Bluetooth communication** with Android phone
- ⚡ **300 RPM gear motors** for high torque and speed
- 🛞 **Motor driver (L298N or similar)** for handling motor movement
- 🎮 **Phone app with buttons/voice** to control the car (forward, back, left, right, stop)
- 🔋 Powered by 7.4V or 11.1V Li-ion/LiPo battery
- 🧠 Optional voice command support using Speech Recognition

---

## 🧩 Technologies Used

- **ESP32** (without Wi-Fi; using only Bluetooth serial)
- **MIT App Inventor** for building the control app
- **Motor Driver Module** (L298N or L9110S)
- **300 RPM BO Motors**
- **HC-05/06** (if using Bluetooth module with Arduino) or native ESP32 Bluetooth
- **Li-ion Battery Pack** (2S or 3S recommended)

---

## 🔌 Circuit Diagram (Basic)

| Component | ESP32 Pin (example) |
|----------|----------------------|
| IN1      | GPIO 27              |
| IN2      | GPIO 26              |
| IN3      | GPIO 25              |
| IN4      | GPIO 33              |
| ENA/ENB  | Connected to VCC or PWM GPIO (optional) |
| Bluetooth (if separate) | RX/TX (via voltage divider for ESP32) |

---

## 📲 Phone App Controls

| Button / Command | Action              |
|------------------|---------------------|
| 🔼 Forward        | Move car forward     |
| 🔽 Backward       | Move car backward    |
| ◀️ Left           | Turn left            |
| ▶️ Right          | Turn right           |
| ⏹️ Stop           | Stop all movement    |
| 🎙️ Voice Command | Recognize and convert to movement |

> Commands are sent as single characters like: `F`, `B`, `L`, `R`, `S`

---

## 🧠 ESP32 Arduino Code Snippet (Sample)

```cpp
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define IN1 27
#define IN2 26
#define IN3 25
#define IN4 33

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_RoboCar");
  pinMode(IN1, OUTPUT); pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT); pinMode(IN4, OUTPUT);
}

void loop() {
  if (SerialBT.available()) {
    char cmd = SerialBT.read();
    if (cmd == 'F') {
      forward();
    } else if (cmd == 'B') {
      backward();
    } else if (cmd == 'L') {
      left();
    } else if (cmd == 'R') {
      right();
    } else if (cmd == 'S') {
      stop();
    }
  }
}

void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void backward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW);
}

void right() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void stop() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}
