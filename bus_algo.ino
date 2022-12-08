/*
Bus Brake Sensor (DPSM Carnival Project)
*/

#include <Servo.h>
#define echo 1
#define trig 2
#define motor1 7
#define motor2 8
#define ena 5

Servo servo; // servo
int del;
long duration; // ultrasonic sensor duration
int distance; // ultrasonic sensor distance
int speed;
int range, immediateRange;
int pos; // position of servo
int max; // max position of servo

void setup() {
  servo.attach(9);
  servo.write(0);
  pos = 0;
  del = 15;
  max = 125;
  range = 30;
  speed = 210;  
  immediateRange = 10;
  pinMode(echo, INPUT); // sets the echoPin an Input
  pinMode(trig, OUTPUT); // sets the trigPin as an Output
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(ena, OUTPUT);
}

void loop() {
  int check = 0;
  for (int i = 0; i < 5; i++) {
    check = check + checkUltraSensor();
  }
  check /= 5;
  if (check <= immediateRange) {
    stopBus();
    delay(1000);
    openDoor();
    delay(2000);
  } else if (check <= range) {
    decelerate();
    stopBus();
    delay(1000);
    openDoor();
    delay(2000);
  } else {
    closeDoor();
    delay(1000);
    accelerate();
  }
}

int checkUltraSensor() {
  digitalWrite(trig, LOW); // makes trigPin low
  delayMicroseconds(2); // 2 micro second delay

  // to release a sound signal for echo
  digitalWrite(trig, HIGH); // tigPin high
  delayMicroseconds(10); // trigPin high for 10 micro seconds
  digitalWrite(trig, LOW); // trigPin low

  duration = pulseIn(echo, HIGH); // read echo pin, time in microseconds
  distance = duration * 0.034 / 2; // calculating actual/real distance

  return distance;
}

int checkIfDoorOpen() {
  if (pos == 0) return 0; // full close
  else if (pos > 0 && pos < max) return 1; // semi/partial
  else if (pos == max) return 2; // full open
}

void openDoor() {
  // open door from current position to max
  for (; pos <= max; pos += 1) {
    servo.write(pos);
    delay(del);
  }
}

void closeDoor() {
  // close door from current position to 0
  for (; pos >= 0; pos -= 1) {
    servo.write(pos);
    delay(del);
  }
}

void accelerate() {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  analogWrite(ena, speed);
}

void decelerate() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  analogWrite(ena, 100);
}

void stopBus() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, LOW);
  analogWrite(ena, 0);
}
