#include <stdlib.h>

#define BLUE_LED 3
#define RED_LED 6
#define GREEN_LED 9

int ByteReceived; //byte from serial
int maxBrightness = 255; //max brightness
int brightness = 0; //brightness for single led

//brightness per colour
int rBright = 0;
int gBright = 0;
int bBright = 0;

int input[10];
int pos = 0;

int byteCount = 0; //amount of bytes gotten from serial

void setup()   //setup
{
  Serial.begin(9600); //serial library

  //pins
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
}


void loop()   //loop
{
  if (Serial.available() > 0) {
    int currentChar;
    while (Serial.available() > 0) { //while input available
      if (pos < 10) { //loop
        currentChar = Serial.read(); //read
        if (currentChar != '\n') {
          input[pos] = currentChar; //store
          pos++; //increment
        } else {
          stringToValues();
          pos = 0; //reset
          //push colours
          analogWrite(RED_LED, rBright);
          analogWrite(GREEN_LED, gBright);
          analogWrite(BLUE_LED, bBright);
        }
        
      }
    }
    
  }
}


void stringToValues () {
  int currentChar;
  int charNr = 0;
  int currentValue;
  
  for (int j = 0; j < 3; j++) { //loop for different leds
    //Serial.println("hier komt die");
    //Serial.println(j);
    currentValue = 0;
    for (int k = 0; k < 3; k++) { //read number for 1 led
      currentValue *= 10;
      currentChar = input[charNr];
      //Serial.println(currentChar);
      currentValue += currentChar - 48;
      //Serial.println(currentValue);
      charNr++;
    }

    switch(j) {
      case 0 : rBright = currentValue; break;
      case 1 : gBright = currentValue; break;
      case 2 : bBright = currentValue; break;
      default: Serial.println("Error in conversion to decimal value");
    }
  }
}
