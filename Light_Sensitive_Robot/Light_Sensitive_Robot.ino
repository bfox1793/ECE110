/*Code for Robot 3: Light Robot
*When robot detects a normal amount of light, it will stand still
*Darkness : robot turns left
*Bright light: robot turns right
*/
#include <Servo.h> 

Servo servoLeft;
Servo servoRight;

const int pushButtonPin = 11;
const float voltageMinimum = 0.05;
const float voltageMaximum = 2.00;
void setup()
{
  Serial.begin(9600);
  servoLeft.attach(12); 
  servoRight.attach(13);
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
  pinMode(pushButtonPin, INPUT);
}

void loop()
{
  float voltageAmount = volts(A3);
  if (voltageAmount < voltageMinimum){
    turnLeft();
  }
  
  else if (voltageAmount > voltageMaximum) {
    turnRight();
  }
  
  else {
    standStill();
  }

}
                                             
float volts(int adPin)                       // Measures volts at adPin
{                                            // Returns floating point voltage
 return float(analogRead(adPin)) * 5.0 / 1024.0;
}    

void standStill(){
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);//servo is slightly off center
  return;
}

void turnRight() {
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(10);
  return;
}

void turnLeft() {
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(10);
  return;
}
