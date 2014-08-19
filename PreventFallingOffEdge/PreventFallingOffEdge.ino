/*Code for DEMO Bot 4
*Robot moves forward until it notices it is falling off edge
*Backs up and turns right if this happens
*/

#include <Servo.h> 

Servo servoLeft;
Servo servoRight;

const int bottomPingPin = 11;
const int pingSensorDistanceConstant = 225;
void setup()
{
  Serial.begin(9600);
  Serial.print("The program has started");
  servoLeft.attach(12); 
  servoRight.attach(13);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);

}

void loop() {
  long currentTime = readPingSensor(bottomPingPin);
  if (currentTime > pingSensorDistanceConstant) {
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1502);//servo is slightly off center
    delay(1000);
    avoidEdge();
  }
  
  else {
    goForward();
  }
}

void avoidEdge() {
 goBackward();
 turnRight();
 return; 
}

void goForward(){
 servoLeft.writeMicroseconds(1700);
 servoRight.writeMicroseconds(1300);
 delay(10);
 return; 
}

void goBackward(){
 servoLeft.writeMicroseconds(1300);
 servoRight.writeMicroseconds(1700);
 delay(500);
 return; 
}

void turnRight() {
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(300);
  return;
}

long readPingSensor(int pingPin){
 long duration;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);          // Set pin to OUTPUT
  digitalWrite(pingPin, LOW);        // Ensure pin is low
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);       // Start ranging
  delayMicroseconds(5);              //   with 5 microsecond burst
  digitalWrite(pingPin, LOW);        // End ranging
  pinMode(pingPin, INPUT);           // Set pin to INPUT

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  duration = pulseIn(pingPin, HIGH);
  
  Serial.println(duration);
  
  return duration;
  
}
