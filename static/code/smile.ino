
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position
const int buttonPin = 5;
int buttonState = 0; 

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  
  // initialize the pushbutton pin as an input, using input pullup:
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);
  
  // check if the pushbutton is pressed.
  if (buttonState == LOW) {
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  myservo.write(0);          // send the servo back to 0
  }

  delay(1000);            // give it enough time to make it there
}
