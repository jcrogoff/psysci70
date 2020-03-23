#include <CapacitiveSensor.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */


CapacitiveSensor   cs_13_7 = CapacitiveSensor(13,7);        // 10M resistor between pins 13 & 7, pin 7 is sensor pin, add a wire and or foil if desired
void setup()                    
{
   cs_13_7.set_CS_AutocaL_Millis(0xFFFFFFFF);     // turn off autocalibrate on channel 1 - just as an example
   Serial.begin(9600);
}

void loop()                    
{
    long start = millis();
    long reading =  cs_13_7.capacitiveSensor(30);
    Serial.print(millis() - start);        // check on performance in milliseconds
    Serial.print("\t");                    // tab character for debug windown spacing
    if (reading < 25) {
      Serial.print("you're good");
    }
    else if (reading < 50) {
      Serial.print("getting a little close there");
    }
    else if (reading < 100) {
      Serial.print("you really need to back up!!");
    }
    else if (reading < 200)  {
      Serial.print("Seriously!! Back up right now!!!");
    }
    else if (reading < 250)  {
      Serial.print("BACK UP RIGHT FREAKING NOW");
    }
    else {
      Serial.print("well. the bomb went off good job.");
    }
    
    Serial.print("\t");

    delay(10);                             // arbitrary delay to limit data to serial port 
}
