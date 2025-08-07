#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

// Define motor control pins
#define IN1 27
#define IN2 26
#define IN3 25
#define IN4 33

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_RoboCar"); // Bluetooth device name
  Serial.println("Bluetooth Started. Waiting for commands...");

  // Set all motor pins as outputs
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  stopMotors();  // Ensure motors are off at start
}

void loop() {
  if (SerialBT.available()) {
    char command = SerialBT.read();
    Serial.print("Received Command: ");
    Serial.println(command);

    switch (command) {
      case 'F': forward(); break;
      case 'B': backward(); break;
      case 'L': left(); break;
      case 'R': right(); break;
      case 'S': stopMotors(); break;
      default: stopMotors(); break;  // Safety stop for unknown command
    }
  }
}

// Motor control functions
void forward() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); // Left motor forward
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); // Right motor forward
}

void backward() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH);
}

void left() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, HIGH); // Left motor backward
  digitalWrite(IN3, HIGH); digitalWrite(IN4, LOW); // Right motor forward
}

void right() {
  digitalWrite(IN1, HIGH); digitalWrite(IN2, LOW); // Left motor forward
  digitalWrite(IN3, LOW); digitalWrite(IN4, HIGH); // Right motor backward
}

void stopMotors() {
  digitalWrite(IN1, LOW); digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW); digitalWrite(IN4, LOW);
}
