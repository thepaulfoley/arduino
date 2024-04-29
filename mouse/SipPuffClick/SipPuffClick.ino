/*
 SipPuffMouseClick

 Description: This sketch is for emulating mouse clicks on a computer using a
 sip/puff switch. It was developed as part of a project using an Arduino
 Leonardo and a NXP MPXV7002DP pressure sensor breakout board. The MPXV7002DP
 connects to the Arduino via V, GND and A0.

 The main loop continuously reads the current pressure from the pressure
 sensor. When the pressure goes below a threshold, the left mouse button is
 pressed. When the pressure goes back above that threshold, the left mouse
 button is released. Similarly, when the pressure exceeds a certain pressure,
 the right mouse button is pressed. When the pressure goes back below that
 threshold, the right mouse button is released.

 NOTE: Use only with boards that support USB emulation. See the following page
 for details: https://www.arduino.cc/reference/en/language/functions/usb/mouse/



 Created March 29, 2024
 by Paul Foley

 This example code is in the public domain.

 https://www.arduino.cc/en/Tutorial/BuiltInExamples/ButtonMouseControl
*/

#include "Mouse.h"

enum OperatingMode { printMode, mouseMode };

// by default, the program will print the sensor values to the serial monitor
OperatingMode mode = printMode;

// set pin number for reading the air pressure from the sensor
const int AIR_PRESSURE_PIN = A0;
// when the air pressure reading from the sensor goes below this threshold, the
// left mouse button will be pressed. When the pressure goes back above this
// threshold, the left mouse button will be released.
const int LEFT_THRESHOLD = 500;
// when the air pressure reading from the sensor goes above this threshold, the
// right mouse button will be pressed. When the pressure goes back below this
// threshold, the right mouse button will be released.
const int RIGHT_THRESHOLD = 1500;
// time (ms) between subsequent readings from the pressure sensor
// 100 ms seems to be a good amount of time
const int responseDelay_ms = 100;
// variable to store the Raw Data value coming from the sensor
int sensorValue = 0;
// variable to store converted kPa value
//  TODO: this variable will store the output from calling the map function. The
//  documentation for the map function says it uses integer math and returns a
//  value of type long. So, check if arduino has a long data type whether it be
//  long, int64_t etc
int outputValue = 0;

void setup() {
  // must be called before doing any mouse emulation
  Mouse.begin();
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ;  // wait for serial port to connect. Needed for native USB port only
  }
  pinMode(AIR_PRESSURE_PIN, INPUT);  // Pressure sensor is on Analogue pin 0
}

void printValues(const int& rawVal, const int& convertedVal) {
  // print the results to the serial monitor:
  Serial.print("sensor = ");
  Serial.print(sensorValue);
  Serial.print("\toutput = ");
  Serial.print(outputValue);
  Serial.println(" % ");
}

void doClick(const int& convertedVal) {
  // if convertedVal < LEFT_THRESHOLD then push/continue pushing the left mouse
  // button
  if (convertedVal < LEFT_THRESHOLD) {
    Mouse.press(MOUSE_LEFT);
  }
  // if convertedVal > RIGHT_THRESHOLD then push/continue pushing the
  // right mouse button
  else if (convertedVal > RIGHT_THRESHOLD) {
    Mouse.press(MOUSE_RIGHT);
  }
  // otherwise release either button that is being pushed
  else {
    Mouse.release(MOUSE_LEFT);
    Mouse.release(MOUSE_RIGHT);
  }
}

void loop() {
  // read the value from the sensor:
  sensorValue = analogRead(AIR_PRESSURE_PIN);
  // map the Raw data to kPa
  outputValue = map(sensorValue, 0, 1023, -100, 100);

  // if mode equals printMode, print the sensor values to the serial monitor
  if (mode == printMode) {
    printValues(sensorValue, outputValue);
  } else {
    doClick(outputValue);
  }

  // wait before moving on to the next iteration of the loop and in turn the
  // next reading from the sensor

  // TODO Mouse.end must be called to end mouse emulation
  if (some_end_condition) {
    Mouse.end();
  }
  delay(responseDelay_ms);
}