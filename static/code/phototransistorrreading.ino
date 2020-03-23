
//Program to Read the Phototransitor

//The pin the phototransistor is connected to
int photoTran = A0;

int led = 7;

//an int variable to keep track of the current reading of the phototransistor
int reading = 0;

void setup(){

  //Set the phototransistor pin as an INPUT reading
  pinMode(photoTran,INPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop(){
  /* respond to the input reading of the phototransistor
    each time the phototransistor "reading" changes, it will update the variable 
    'reading' and print the new reading to the console
    the delay is to ensure that the reading is only updated every 100ms 
    (otherwise there would be a million print statements) */
  reading = analogRead(photoTran);
  Serial.println(reading);

  //if it is dark
  if (reading >= 1023) {
    //turn the LED on
    digitalWrite(led, HIGH);
    }
  else  {
    //turn the LED off
    digitalWrite(led, LOW);
    }
  delay(100);
}
