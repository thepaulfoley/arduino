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

// set pin number for reading the air pressure from the sensor
const int AIR_PRESSURE_PIN = 2;
// when the air pressure reading from the sensor goes below this threshold, the
// left mouse button will be pressed. When the pressure goes back above this
// threshold, the left mouse button will be released.
const int LEFT_THRESHOLD = 500;
// when the air pressure reading from the sensor goes above this threshold, the
// right mouse button will be pressed. When the pressure goes back below this
// threshold, the left mouse button will be released.
const int RIGHT_THRESHOLD = 1500;
int responseDelay_ms = 10;  // time (ms) between subsequent readings from the pressure sensor

void setup() {
  // initialize the buttons' inputs:
  pinMode(AIR_PRESSURE_THRESHOLD, ANALOG);
  pinMode(downButton, INPUT);
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);
  pinMode(mouseButton, INPUT);
  // initialize mouse control:
  Mouse.begin();
}

void loop() {
  // read the buttons:
  int upState = digitalRead(upButton);
  int downState = digitalRead(downButton);
  int rightState = digitalRead(rightButton);
  int leftState = digitalRead(leftButton);
  int clickState = digitalRead(mouseButton);

  // calculate the movement distance based on the button states:
  int xDistance = (leftState - rightState) * range;
  int yDistance = (upState - downState) * range;

  // if X or Y is non-zero, move:
  if ((xDistance != 0) || (yDistance != 0)) {
    Mouse.move(xDistance, yDistance, 0);
  }

  // if the mouse button is pressed:
  if (clickState == HIGH) {
    // if the mouse is not pressed, press it:
    if (!Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.press(MOUSE_LEFT);
    }
  }
  // else the mouse button is not pressed:
  else {
    // if the mouse is pressed, release it:
    if (Mouse.isPressed(MOUSE_LEFT)) {
      Mouse.release(MOUSE_LEFT);
    }
  }

  // a delay so the mouse doesn't move too fast:
  delay(responseDelay);
}
