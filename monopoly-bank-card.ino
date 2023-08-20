#include "include/Display7Seg_MM5450.h"

#define BITSB 8                        // number of bits per byte, used for code clarity
#define DATABITS 36                    // what we must send to the chip in order to control the lights
#define STARTBIT 1                     // value of the starting bit;  

const int clockPin  = 13;              // connect Arduino pin 3 to clock pin (21) on the 5450
const int dataPin   = 12;              // connect Arduino pin 6 to data pin (22) on the 5450
const int delayTime = 500;             // delay between lights

const int arrayLen  = (int)((DATABITS-1)/BITSB) + 1; 

byte ledArray[arrayLen];               // for this chip, length is 5 and that could hold 40 values    

typedef enum {                         // this exists primarily for code clarity
  OFF, ON
} ledState;

auto ds = Display7Seg_MM5450(clockPin, dataPin);

// Start program -------------------------------------------------------------------------------------
//
void setup() {
  pinMode(clockPin, OUTPUT);           // we don't need a latch pin since the 5450/5451 latched after
  pinMode(dataPin,  OUTPUT);           // receiving the 36 databits
  ds.send(0);
  delay(delayTime);
}

void loop() {
  for (int i=0; i<10000; i++){
    ds.send(i);
    delay(5);
  }
}
