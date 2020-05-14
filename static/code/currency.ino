//Note -- by accident I revearsed my US motor during the building phase. Thus, the degrees coded for US are all inverted (ie. 180-wanted degree) to get the actual desired value.

// Include the Servo library 
#include <Servo.h> 

// Declare the Servo pins 
int servoPin_EUR = 12; 
int servoPin_US = 10;
int servoPin_YEN = 7; 
 
// Create servo objects 
Servo Servo_EUR; 
Servo Servo_US; 
Servo Servo_YEN;

//numbers for calculation
int strength_high = 4987;
int strength_low = -4291;
int strength_EUR = 113;
int strength_US = 4987;
int strength_YEN = -4291;
 
void setup() { 
   Serial.begin(9600);
   // Attach the servos to the used pin numbers 
   Servo_EUR.attach(servoPin_EUR);
   Servo_US.attach(servoPin_US);
   Servo_YEN.attach(servoPin_YEN);
}


int calculate_degrees (int strength) {
  int base = strength_high-strength_low;
  Serial.println(base);
  strength = strength - strength_low;
  Serial.println(strength);
  int diff = strength*100/base;
  Serial.println(diff);
  int deg = (diff * 180)/100;
  Serial.println(deg);
  return deg;
}

void loop(){ 
  
   // Make servos go to 0 degrees 
   Servo_EUR.write(0); 
   Servo_US.write(0); 
   Servo_YEN.write(0);

   //Calculate Degree Change
   Serial.print("EUR");
   int EUR_deg = calculate_degrees(strength_EUR);
   Serial.print("US");
   int US_deg = 180 - calculate_degrees(strength_US);
   Serial.print("YEN");
   int YEN_deg = calculate_degrees(strength_YEN);
   delay(1000); 
   
   // Make servos go to desired degree
   Servo_EUR.write(EUR_deg); 
   Servo_US.write(US_deg); 
   Servo_YEN.write(YEN_deg); 
   delay(1000); 
}
