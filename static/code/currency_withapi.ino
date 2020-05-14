//Note -- by accident I revearsed my US motor during the building phase. Thus, the degrees coded for US are all inverted (ie. 180-wanted degree) to get the actual desired value.

// Include the libraries 
#include <Servo.h> 
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "YOUR_SSID";
const char* password =  "YOUR_PASSWORD";
 
const String endpoint = "https://api.exchangeratesapi.io/latest";

// Declare the Servo pins 
int servoPin_EUR = 12; 
int servoPin_US = 27;
int servoPin_YEN = 33; 
 
// Create servo objects 
Servo Servo_EUR; 
Servo Servo_US; 
Servo Servo_YEN;
 
void setup() { 
   Serial.begin(9600);
   // Attach the servos to the used pin numbers 
   Servo_EUR.attach(servoPin_EUR);
   Servo_US.attach(servoPin_US);
   Servo_YEN.attach(servoPin_YEN);

   Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  Serial.println("Connected to the WiFi network");
}


int calculate_degrees (float strength, float strength_high, float strength_low) {
  float base = strength_high-strength_low;
  Serial.println(base);
  strength = strength - strength_low;
  Serial.println(strength);
  float diff = strength/base;
  Serial.println(diff);
  float deg = diff * 180;
  Serial.println(deg);
  return (int) deg;
}

float get_max (float i, float j, float k) {
  int ret = i>j ? i : j;
  ret = k>ret ? k : ret;
  return ret;
}

float get_min (float i, float j, float k) {
  int ret = i<j ? i : j;
  ret = k<ret ? k : ret;
  return ret;
}

void loop(){ 
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status

    HTTPClient http;

    http.begin(endpoint); //Specify the URL
    int httpResponseCode = http.GET();  // Make the GET request

    if (httpResponseCode > 0) {   // Execute if we get a good response

      String payload = http.getString();
      Serial.println(httpResponseCode);
      // Serial.println(payload); // Uncomment to view the entire payload

      DynamicJsonDocument doc(10000); // Create a buffer of 10000 bytes

      // Deserialize the JSON document
      DeserializationError error = deserializeJson(doc, payload);

      // Test if parsing succeeds.
      if (error) {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return;
      }

      // Navigate through JSON document, extracting some values
      const float strength_EUR = doc["rates"]["EUR"];
      const float strength_US = doc["rates"]["USD"];
      const float strength_YEN = doc["rates"]["JPY"];
      
      float strength_high = get_max(strength_EUR, strength_US, strength_YEN);
      float strength_low = get_min(strength_EUR, strength_US, strength_YEN);

     //Calculate Degree Change
     Serial.print("EUR");
     int EUR_deg = calculate_degrees(strength_EUR, strength_high, strength_low);
     Serial.print("US");
     int US_deg = 180 - calculate_degrees(strength_US, strength_high, strength_low);
     Serial.print("YEN");
     int YEN_deg = calculate_degrees(strength_YEN, strength_high, strength_low);
     delay(1000); 
  
     //Calculate Degree Start
     Serial.print("EUR");
     int EUR_start = EUR_deg=0 ? 180 : 0;
     Serial.print("US");
     int US_start = 180 - (US_deg=0 ? 180 : 0);;
     Serial.print("YEN");
     int YEN_start = YEN_deg=0 ? 180 : 0;
     delay(1000); 
    
     // Make servos go to 0 degrees 
     Servo_EUR.write(EUR_start); 
     Servo_US.write(US_start); 
     Servo_YEN.write(YEN_start);
     
     // Make servos go to desired degree
     Servo_EUR.write(EUR_deg); 
     Servo_US.write(US_deg); 
     Servo_YEN.write(YEN_deg); 
      
      http.end();   // Close the connection
    }

    delay(30000); // Wait 30 seconds between requests 

  }

}
