/*Code for DEMO Bot 4
*This robot makes use of the PING sensor
*Robot will move forward constantly, unless its PING sensors are utilized
*If robot detects an object in front of it, it will back up and turn slightly left
*If this happens three times, the red LED will turn on, the robot will dance, and then it will back up
*If the robot detects the ground in front of it is missing, it will pause, back up, and turn right
*/

#include <Servo.h> 

Servo servoLeft;
Servo servoRight;

const int bottomPingPin = 11;
const int frontPingPin = 3;
const int redLedPin = 2;
const int pingSensorGroundDistanceConstant = 225;
const int pingSensorFrontDistanceConstant = 750;
const int danceConstant = 3;
int frontObjectDetectionCount = 0;
void setup()
{
  Serial.begin(9600);
  Serial.print("The program has started");
  servoLeft.attach(12); 
  servoRight.attach(13);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  pinMode(redLedPin, OUTPUT);
}

void loop() {
  digitalWrite(redLedPin, LOW);
  long bottomPingDistance = readPingSensor(bottomPingPin);
  long frontPingDistance = readPingSensor(frontPingPin);
  
  if (bottomPingDistance > pingSensorGroundDistanceConstant) {
    standStill();
    delay(1000);
    avoidEdge();
  }
  
  if (frontPingDistance < pingSensorFrontDistanceConstant) {
    frontObjectDetectionCount++;
    if (frontObjectDetectionCount > 2){
      digitalWrite(redLedPin, HIGH);
      dance();
      frontObjectDetectionCount=0;
    }
    digitalWrite(redLedPin, LOW);
    avoidEdge(); 
  }
  
  goForward();
}

void standStill(){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1502);//servo is slightly off center
  delay(10);
  return;
}

void dance(){
 goBackward();
 delay(100);
 goForward();
 delay(100);
 for (int i=0;i<danceConstant;i++){
   turnRight();
   turnLeft();
 }
 return; 
}

void avoidEdge() {
 goBackward();
 delay(500);
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
 delay(10);
 return; 
}

void turnRight() {
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(300);
  return;
}

void turnLeft() {
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
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
  return duration;
}
