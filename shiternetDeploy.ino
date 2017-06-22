#include "config.h"

const int buttonPin = 2; //Hall Effect Sensor
int buttonState = 0; //Intitial state of sensor
int lastButtonState = 0; //Most recent state of sensor
int revolutions = 0; //Number of times sensor is triggered. Each trigger represents 1 revolution

AdafruitIO_Feed *digital = io.feed("tp");

void setup()
{  
  Serial.begin(115200);           // set up Serial library at 9600 bps
  pinMode(buttonPin, INPUT);
  delay(100);

  // We start by connecting to a WiFi network
    // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void loop()
{ 
  io.run();

  buttonState = digitalRead(buttonPin);
  if (buttonState != lastButtonState){
    if (buttonState == HIGH){
      revolutions++;
      Serial.print("sending revolutions number -> ");
      Serial.println(revolutions);
      digital->save(revolutions);
    }
  }
  
  lastButtonState = buttonState;
}
