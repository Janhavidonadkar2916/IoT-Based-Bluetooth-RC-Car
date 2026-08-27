#include <SoftwareSerial.h>

// Bluetooth Module HC-05
SoftwareSerial bluetooth(10, 11);
// RX, TX

// Motor Driver Pins
#define ENA 5
#define IN1 6
#define IN2 7

#define ENB 9
#define IN3 8
#define IN4 12

// Motion Sensor Pin
#define MOTION_SENSOR 4

// Buzzer Pin
#define BUZZER 3

char command;

void setup() {

  // Motor Driver Pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Motion Sensor
  pinMode(MOTION_SENSOR, INPUT);

  // Buzzer
  pinMode(BUZZER, OUTPUT);

  // Serial Communication
  Serial.begin(9600);

  // Bluetooth Communication
  bluetooth.begin(9600);

  // Set Motor Speed
  analogWrite(ENA, 200);
  analogWrite(ENB, 200);

  // Initially stop the car
  stopCar();

  Serial.println("Bluetooth RC Car Ready!");
}

void loop() {

  // Read Bluetooth Commands
  if (bluetooth.available()) {

    command = bluetooth.read();

    Serial.println(command);

    switch (command) {

      case 'F':
        moveForward();
        break;

      case 'B':
        moveBackward();
        break;

      case 'L':
        turnLeft();
        break;

      case 'R':
        turnRight();
        break;

      case 'S':
        stopCar();
        break;
    }
  }

  // Motion Detection
  int motionDetected = digitalRead(MOTION_SENSOR);

  if (motionDetected == HIGH) {

    Serial.println("Motion Detected!");

    digitalWrite(BUZZER, HIGH);

    // Stop car when motion is detected
    stopCar();

    delay(500);

  } else {

    digitalWrite(BUZZER, LOW);
  }
}


// ================= MOTOR FUNCTIONS =================

// Move Forward
void moveForward() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


// Move Backward
void moveBackward() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


// Turn Left
void turnLeft() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}


// Turn Right
void turnRight() {

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}


// Stop Car
void stopCar() {

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
