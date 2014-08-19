#include <Servo.h> 

Servo servoLeft;
Servo servoRight;


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
  servoLeft.writeMicroseconds(1500);
  servoRight.writeMicroseconds(1500);
}
