/*
 * Code by Yodha Ardiansyah
 * Instagram: @yodhaar_
 */

#include <Servo.h>

Servo servo;

int SRV = 2; // Servo
int ENA = 5; // Enable A
int ENB = 6; // Enable B
int IN1 = 9; // Input 1
int IN2 = 10; // Input 2
int IN3 = 11; // Input 3
int IN4 = 12; // Input 4

char val;
int myservo = 180;
int ena_speed = 102;
int enb_speed = 105;
bool moving = false;
bool reversing = false;
int original_value = 102;

void setup() {
  servo.attach(SRV);
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  servo.write(myservo);
}

void loop() {
  if (val == 'D') { // OPEN
    if (myservo <= 180) {
      myservo += 4;
      delay(30);
      servo.write(myservo);
    }
  }
  if (val == 'I') { // CLOSE
    if (myservo >= 135) {
      myservo -= 4;
      delay(30);
      servo.write(myservo);
    }
  }
  if (val == 'C') { // START OPENING GRIPPER
    if (myservo <= 180) {
      myservo = 180;
      delay(30);
      servo.write(myservo);
    }
  }
  if (val == 'A') {
    if (ena_speed < 252 && enb_speed < 255) {
      ena_speed += 50;
      enb_speed += 50;
      delay(100);
    }
  }
  if (val == 'Y') {
    if (ena_speed > 102 && enb_speed > 105) {
      ena_speed -= 50;
      enb_speed -= 50;
      delay(100);
    }
  }

  while (Serial.available() > 0) {
    val = Serial.read();
    Serial.println(val);
  }

  // Motor Driver Control
  if (val == 'F') {
    // MOVE FORWARD
    if (!moving) {
      moving = true;
      analogWrite(ENA, 102);
      analogWrite(ENB, 105);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      delay(100);
    } else {
      analogWrite(ENA, ena_speed);
      analogWrite(ENB, enb_speed);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
  } else if (val == 'B') {
    // MOVE BACKWARD
    if (!moving) {
      moving = true;
      original_value = enb_speed;
      enb_speed -= (enb_speed * 0.02);
      reversing = true;
      analogWrite(ENA, 102);
      analogWrite(ENB, 105);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      delay(100);
    } else {
      analogWrite(ENA, ena_speed);
      analogWrite(ENB, enb_speed);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
  } else if (val == 'R') {
    // TURN LEFT
    if (!moving) {
      moving = true;
      analogWrite(ENA, 102);
      analogWrite(ENB, 105);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
      delay(100);
    } else {
      if (ena_speed == 102 && enb_speed == 105) {
        analogWrite(ENA, ena_speed);
        analogWrite(ENB, enb_speed);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      } else {
        analogWrite(ENA, ena_speed - 50);
        analogWrite(ENB, enb_speed - 50);
        digitalWrite(IN1, LOW);
        digitalWrite(IN2, HIGH);
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
      }
    }
  } else if (val == 'L') {
    // TURN RIGHT
    if (!moving) {
      moving = true;
      analogWrite(ENA, 102);
      analogWrite(ENB, 105);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
      delay(100);
    } else {
      if (ena_speed == 102 && enb_speed == 105) {
        analogWrite(ENA, ena_speed);
        analogWrite(ENB, enb_speed);
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      } else {
        analogWrite(ENA, ena_speed - 50);
        analogWrite(ENB, enb_speed - 50);
        digitalWrite(IN1, HIGH);
        digitalWrite(IN2, LOW);
        digitalWrite(IN3, LOW);
        digitalWrite(IN4, HIGH);
      }
    }
  } else if (val == 'S') {
    moving = false;
    if (reversing) {
      reversing = false;
      enb_speed = original_value;
    }
    // STOP
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, LOW);
  }
  Serial.print(ena_speed);
  Serial.print(enb_speed);
}
