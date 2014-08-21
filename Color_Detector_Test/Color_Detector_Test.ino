/* ColorPal Sensor Example for Arduino
  Author: Martin Heermance, with some assistance from Gordon McComb
  This program drives the Parallax ColorPAL color sensor and provides
  serial RGB data in a format compatible with the PC-hosted
  TCS230_ColorPAL_match.exe color matching program.
*/

#include <SoftwareSerial.h>

const int colorDetectorPin = 2; // ColorPAL connected to pin 2
const int unused = 255;         // Non-existant pin # for SoftwareSerial
const int sioBaud = 4800;
const int waitDelay = 200;

// Received RGB values from ColorPAL
int red;
int grn;
int blu;

// Set up two software serials on the same pin.
SoftwareSerial serin(colorDetectorPin, unused);
SoftwareSerial serout(unused, colorDetectorPin);

void setup() {
  Serial.begin(9600);
  resetColorPal(colorDetectorPin);    // Send reset to ColorPal
  serout.begin(sioBaud);
  pinMode(colorDetectorPin, OUTPUT);
  serout.print("= (00 $ m) !"); // Loop print values, see ColorPAL documentation
  serout.end();              // Discontinue serial port for transmitting

  serin.begin(sioBaud);            // Set up serial port for receiving
  pinMode(colorDetectorPin, INPUT);
  Serial.println("Beginning Program");
}

void loop() {
  readData();
}  

// Reset ColorPAL; see ColorPAL documentation for sequence
void resetColorPal(int pin) {
  delay(200);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  pinMode(pin, INPUT);
  while (digitalRead(pin) != HIGH);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
  delay(80);
  pinMode(pin, INPUT);
  delay(waitDelay);
}

void readData() {
  char buffer[32];
 
  if (serin.available() > 0) {
    // Wait for a $ character, then read three 3 digit hex numbers
    buffer[0] = serin.read();
    if (buffer[0] == '$') {
      for(int i = 0; i < 9; i++) {
        while (serin.available() == 0);     // Wait for next input character
        buffer[i] = serin.read();
        if (buffer[i] == '$')               // Return early if $ character encountered
          return;
      }
      parseAndPrint(buffer);
      delay(10);
    }
  }
}

// Parse the hex data into integers
void parseAndPrint(char * data) {
  sscanf (data, "%3x%3x%3x", &red, &grn, &blu);
  char buffer[32];
  sprintf(buffer, "R%4.4d G%4.4d B%4.4d", red, grn, blu);
  Serial.println(buffer);
}
