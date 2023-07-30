#include "Adafruit_NeoPixel.h"

#define LED_COUNT 4
#define LED_PIN 7
Adafruit_NeoPixel strip = Adafruit_NeoPixel (LED_COUNT, LED_PIN, NEO_GRB+NEO_KHZ800);

const int buttonPin = 2;

bool isGreen = false;
bool isShowed  = false;

unsigned long timestamp = 0;
int currentLed = 0;

void setup(){
  strip.begin();
  pinMode(buttonPin, INPUT);
}

void loop(){

  handleButtonInput();
  updateLed();
  
}

bool isChangeHandled = false;

void handleButtonInput(){
  
  int buttonState = digitalRead(buttonPin);
  
  if(buttonState == 1)
  {
    if(!isChangeHandled)
    {
      isGreen = !isGreen;
      isChangeHandled = true;
      return;
    }
  }
  else
  	isChangeHandled = false;
}


void updateLed(){
  
  if(isShowed){
  	if(millis()-timestamp<500)
    	return;
    else
      isShowed = false;
  }
  
  for(int i=0; i<LED_COUNT;i++){
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  
  if(isGreen)
    strip.setPixelColor(currentLed, strip.Color(0, 255, 0));
  else
    strip.setPixelColor(currentLed, strip.Color(255, 0, 0));
    
  strip.show();
  
  isShowed = true;
  timestamp = millis();
  
  if(currentLed!=LED_COUNT)
  	currentLed++;
  else
    currentLed = 0;
  }
