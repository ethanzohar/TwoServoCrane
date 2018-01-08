/*
  Crane assignment
  Code by Ethan, someother work by Brain
  Date: November, 16, 2017
  Uses a joystick to control a 2 axis servo crane
*/

#include <Servo.h> // Includes the servo library

Servo myservoHor;  // create servo object to control a servo
Servo myservoVer;  // create servo object to control a servo

int joyPinX = A0;  // analog pin used to connect the potentiometer
int joyPinY = A1;  // analog pin used to connect the potentiometer
int joyPinButton = 52;

int holdX = 90; // Original saved
int holdY = 90; // position

int x = 90; // Current position
int y = 90; // of servos

int newX; // Variable for
int newY; // new position

bool buttonTrigger = true;

int delayTime = 10; // Speed of crane movement
int threshold = 10; // Reduces range of servo to reduce fault in movement

void setup() {
  myservoHor.attach(9);  // attaches the servo on pin 9 to the servo object
  myservoVer.attach(10);  // attaches the servo on pin 10 to the servo object

  pinMode(joyPinX, INPUT);
  pinMode(joyPinY, INPUT);
  pinMode(joyPinButton, INPUT_PULLUP);

  Serial.begin(9600);

  for (int i = 180; i >= 0; i--) {    //
    myservoHor.write(i);              //
    myservoVer.write(i);              //
    delay(delayTime);                 //
  }                                   // Moves the position of the servos to the center
  for (int i = 0; i <= 90; i++) {     //
    myservoHor.write(i);              //
    myservoVer.write(i);              //
    delay(delayTime);                 //
  }
}

void loop() {
  float joyX = analogRead(joyPinX);             //
  float joyY = analogRead(joyPinY);             // Sets inputs from the Joystick
  int joyButton = !digitalRead(joyPinButton);   //

  if (joyButton and buttonTrigger) { //If the button has been pressed
    newX = holdX; // Sets new position
    newY = holdY; // as the old saves position
    holdX = x;  // Saves current
    holdY = y;  // position
    homing(); // Function to move servos to new position
    buttonTrigger = false;
  } else {
    if (joyX > 520) {           //
      if (x > threshold) {      //
        x--;                    //
      }                         //
    } else if (joyX < 490) {    //
      if (x < 180) {            //
        x++;                    //
      }                         //
    }                           // Uses the input of the joystick
    if (joyY > 520) {           // To correlate movment on the servos
      if (y > threshold) {      //
        y--;                    //
      }                         //
    } else if (joyY < 490) {    //
      if (y < 180) {            //
        y++;                    //
      }                         //
    }                           //
    delay(delayTime);
    myservoHor.write(x);  // Write to the
    myservoVer.write(y);  // Servos
  }

  if (joyButton == false) { // If the button is released
    buttonTrigger = true;   // Allow the button to be pressed again
  }
}

void homing() {
  if (x <= newX) {  // If x needs to move right
    for (int i = x; i <= newX; i++) {
      x = i;
      myservoHor.write(i);
      delay(delayTime);
    }
  } else if (x >= newX) {  // If x needs to move left
    for (int i = x; i >= newX; i--) {
      x = i;
      myservoHor.write(i);
      delay(delayTime);
    }
  }

  if (y <= newY) {  // If y needs to move up
    for (int i = y; i <= newY; i++) {
      y = i;
      myservoVer.write(i);
      delay(delayTime);
    }
  } else if (y >= newY) {  // If y needs to move down
    for (int i = y; i >= newY; i--) {
      y = i;
      myservoVer.write(i);
      delay(delayTime);
    }
  }
}

