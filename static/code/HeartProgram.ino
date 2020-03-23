#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define STRIP_PIN    5
#define STRIP_LED_COUNT 17

//The pin the phototransistor is connected to
int photoTran = A0;

//an int variable to keep track of the current reading of the phototransistor
int pt_reading = 0;

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(STRIP_LED_COUNT, STRIP_PIN, NEO_GRB + NEO_KHZ800);

int c = strip.Color(255, 0, 0);  // define the variable c as RED (R,G,B)

void setup(){

  //Set the phototransistor pin as an INPUT reading
  pinMode(photoTran,INPUT);
  strip.begin();               // initialize strip
  strip.show();                // Update all LEDs (= turn OFF, since none of them have been set yet!)
}

void loop(){
  /* respond to the input reading of the phototransistor
    each time the phototransistor "reading" changes, it will update the variable 
    'reading' and print the new reading to the console */
  pt_reading = analogRead(photoTran);
  Serial.println(pt_reading);

  //if it is dark
  if (pt_reading >= 1023) {
    colorWipe(strip.Color(255,   0,   0), 50); // Red
    strip.clear();  // turn off all LEDS
    strip.show(); // visibly update the state of the strip
    
  }
  else  {
    strip.clear();  // turn off all LEDS
    strip.show(); // visibly update the state of the strip
  }
}

// Some functions of our own for creating animated effects -----------------

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    pt_reading = analogRead(photoTran);
    if (pt_reading < 1023) {
      Serial.println("recognized the offstate");
      strip.clear();  // turn off all LEDS
      strip.show(); // visibly update the state of the strip
      return;
    }
    else {
      delay(wait);                           //  Pause for a moment 
      strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
      strip.show();                          //  Update strip to match

    }
  }
}
