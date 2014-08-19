/*Code for Demo Robot #1
*Features:
*Line following
*Attempt to correct self when falling off line by backing up and shifting left
*Also will beep if detected off line
*Green LED - Driving straight
*Yellow LED - Adjusting to stay on line
*Red LED - Off the line entirely
*/

#include <Servo.h> 

Servo servoLeft;
Servo servoRight;
int greenLed = 11;
int yellowLed = 9;
int redLed = 7;
int offLineCount;

void setup()
{
  Serial.begin(9600);
  Serial.print("The program has started");
  servoLeft.attach(12); 
  servoRight.attach(13);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  pinMode(greenLed, OUTPUT);
  pinMode(yellowLed, OUTPUT);
  pinMode(redLed, OUTPUT);
  offLineCount = 0;
}

void loop() {
  followLine();
}

void followLine(){
  int blackLineConstant = 50;
  long leftQti = RCTime(10);
  long middleQti = RCTime(6);
  long rightQti = RCTime(2);
  
  boolean leftOnLine = leftQti > blackLineConstant;
  boolean middleOnLine = middleQti > blackLineConstant;
  boolean rightOnLine = rightQti > blackLineConstant;

  digitalWrite(greenLed, LOW);
  digitalWrite(yellowLed, LOW);
  digitalWrite(redLed, LOW);
  
  //Perfectly on line, go straight
  if (!leftOnLine && middleOnLine && !rightOnLine){
    digitalWrite(greenLed, HIGH);
    goForward();
    offLineCount = 0;
  }
  
  //Slight left
  else if (leftOnLine && middleOnLine && !rightOnLine){
    digitalWrite(yellowLed, HIGH);
    slightLeft();
    offLineCount = 0;
  }
  
  //Slight right
  else if (!leftOnLine && middleOnLine && rightOnLine){
    digitalWrite(yellowLed, HIGH);
    slightRight();
    offLineCount = 0;
  }
  
  //Adjust left
  else if (leftOnLine && !middleOnLine && !rightOnLine){
    digitalWrite(yellowLed, HIGH);
    goLeft();
  }
  
  //Adjust right
  else if (!leftOnLine && !middleOnLine && rightOnLine){
    digitalWrite(yellowLed, HIGH);
    goRight();
    delay(100);
    offLineCount = 0;
  }
  
  else {
    Serial.println(offLineCount);
    offLineCount++;
    servoLeft.writeMicroseconds(1500);
    servoRight.writeMicroseconds(1500);
    if (offLineCount > 5){
      offLineCount=0;
      retreat();
    }
    digitalWrite(redLed, HIGH);
    delay(250);
  }

}

void retreat(){
  tone(3,500,1000);
  delay(1000);
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1700);
  delay(1000);
  slightLeft();
  return; 
}

void slightLeft(){
  servoLeft.writeMicroseconds(1475);
  servoRight.writeMicroseconds(1475);
  delay(100);
  return;
}

void slightRight(){
  servoLeft.writeMicroseconds(1525);
  servoRight.writeMicroseconds(1525);
  delay(100);
  return;
}

void goLeft(){
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(100);
  return;
}
void goRight(){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(100);
  return;
}

void goForward(){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(200);
  return;
}

long RCTime(int sensorIn) {
  long duration = 0;
  pinMode(sensorIn, OUTPUT); // Sets pin as OUTPUT
  digitalWrite(sensorIn, HIGH); // Pin HIGH
  delay(1); // Waits for 1 millisecond
  pinMode(sensorIn, INPUT); // Sets pin as INPUT
  digitalWrite(sensorIn, LOW); // Pin LOW

  while(digitalRead(sensorIn)) { // Waits for the pin to go LOW
    duration++;
  }

return duration; // Returns the duration of the pulse
}
