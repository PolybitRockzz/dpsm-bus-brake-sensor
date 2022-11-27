/*
Bus Brake Sensor Experimental (DPSM Carnival Project)
*/

#include <Servo.h>
#define trig 2
#define echo 1

Servo servo; // servo
long duration; // ultrasonic sensor duration
int distance; // ultrasonic sensor distance
int range; // range of ultrasonic sensor
int pos; // position of servo
int max; // max position of server

void setup() {
  servo.attach(9);
  pos = 0;
  max = 105;
  range = 30;
  pinMode(trig, OUTPUT); // sets the trigPin as an Output
  pinMode(echo, INPUT); // sets the echoPin as an Input
}

void loop() {
  checkUltraSensor();
  if(distance <= range) {
    openDoor();
  } else {
    closeDoor();
  }
}

void revalidate() {
  int i = 0;
  for (i = 0; i <= max; i += 1) {
    servo.write(i);
    delayMicroseconds(15);
  }
  for (i = max; i >= 0; i -= 1) {
    servo.write(i);
    delayMicroseconds(15);
  }
}

void checkUltraSensor() {
  digitalWrite(trig, LOW); // makes trigPin low
  delayMicroseconds(5); // 2 micro second delay

  // to release a sound signal for echo
  digitalWrite(trig, HIGH); // tigPin high
  delayMicroseconds(10); // trigPin high for 10 micro seconds
  digitalWrite(trig, LOW); // trigPin low

  duration = pulseIn(echo, HIGH); // read echo pin, time in microseconds
  distance = duration * 0.034 / 2; // calculating actual/real distance
}

int checkIfDoorOpen() {
  if (pos == 0) return 0; // full close
  else if (pos >= 0 && pos <= max) return 1; // semi/partial
  else if (pos == max) return 2; // full open
}

void openDoor() {
  // open door one notch
  pos += 1;
  servo.write(pos);
}

void closeDoor() {
  // close door one notch
  pos -= 1;
  servo.write(pos);
}