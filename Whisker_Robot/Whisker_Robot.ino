/*Robot #2: Whisker Robot
*If left whisker is touched, robot will turn right
*If right whisker is touched, robot will turn left
*If both whisker are touched, robot will pause and then turn around
*/

#include <Servo.h> 

const int rightWhisker = 5;
const int leftWhisker = 7;
Servo servoLeft;
Servo servoRight;

void setup()
{
  pinMode(leftWhisker, INPUT);
  pinMode(rightWhisker, INPUT); 
  
  servoLeft.attach(13); 
  servoRight.attach(12);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);

  Serial.begin(9600);
}  
 
void loop()
{
  byte rightWhiskerTouched = !digitalRead(rightWhisker);
  byte leftWhiskerTouched= !digitalRead(leftWhisker);
  
  if (leftWhiskerTouched && rightWhiskerTouched) {
    turnAround();
    Serial.println("Both are touched!");
  }
  
  else if (leftWhiskerTouched){ //Object detected on left of robot
    turnRight();
    Serial.println("Left is touched");
  }
  
  else if (rightWhiskerTouched) {
    turnLeft();
    Serial.println("Right is touched");
  }
  
  goForward();  
  delay(50);  
}   

void turnAround() { //Stop for 1.5 seconds, then turn around
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  delay(1500);
  turnLeft();
  turnLeft();  
}

void goForward(){
 servoLeft.writeMicroseconds(1700);
 servoRight.writeMicroseconds(1300);
 delay(10);
 return; 
}

void turnRight() {
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(500);
  return;
}

void turnLeft() {
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(500);
  return;
}
