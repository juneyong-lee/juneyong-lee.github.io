
#include <Wire.h>
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 6
#define DHTTYPE    DHT22     // DHT 22 (AM2302)
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

Adafruit_AlphaNum4 alpha4 = Adafruit_AlphaNum4();

static int pinA = 2; // Our first hardware interrupt pin is digital pin 2
static int pinB = 3; // Our second hardware interrupt pin is digital pin 3
volatile int aFlag = 0; // let's us know when we're expecting a rising edge on pinA to signal that the encoder has arrived at a detent
volatile int bFlag = 0; // let's us know when we're expecting a rising edge on pinB to signal that the encoder has arrived at a detent (opposite direction to when aFlag is set)
int encoderPos = 20; //this variable stores our current value of encoder position. Change to int or uin16_t instead of byte if you want to record a larger range than 0-255
volatile int oldEncPos = 0; //stores the last encoder position value so we can compare to the current reading and see if it has changed (so we know when to print to the serial monitor)
volatile int reading = 0; //somewhere to store the direct values we read from our interrupt pins before checking to see if we have moved a whole detent

uint8_t ones, tens;
int nF;
int nS;

uint8_t temp_ones, temp_tens;
int tF;
int tS;
int temp;

const int mosPin = 10;

int fan = 9;
int fanSpeed;
int heat = 0;

void setup() {

  pinMode(mosPin, OUTPUT);

  pinMode(pinA, INPUT_PULLUP); // set pinA as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  pinMode(pinB, INPUT_PULLUP); // set pinB as an input, pulled HIGH to the logic voltage (5V or 3.3V for most cases)
  attachInterrupt(0, PinA, RISING); // set an interrupt on PinA, looking for a rising edge signal and executing the "PinA" Interrupt Service Routine (below)
  attachInterrupt(1, PinB, RISING); // set an interrupt on PinB, looking for a rising edge signal and executing the "PinB" Interrupt Service Routine (below)

  Serial.begin(9600);
  alpha4.begin(0x70);
  //  alpha4.clear();
  //  alpha4.writeDisplay();

  dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);

  pinMode(fan, OUTPUT);

}


void PinA() {
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; // read all eight pin values then strip away all but pinA and pinB's values
  if (reading == B00001100 && aFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos --; //decrement the encoder's position count
    //    if (encoderPos <= 0 ) {
    //      encoderPos = 16;
    //    }
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn

  }
  else if (reading == B00000100) bFlag = 1; //signal that we're expecting pinB to signal the transition to detent from free rotation
  sei(); //restart interrupts
}

void PinB() {
  cli(); //stop interrupts happening before we read pin values
  reading = PIND & 0xC; //read all eight pin values then strip away all but pinA and pinB's values
  if (reading == B00001100 && bFlag) { //check that we have both pins at detent (HIGH) and that we are expecting detent on this pin's rising edge
    encoderPos ++; //increment the encoder's position count
    //    if (encoderPos >= 17) {
    //      encoderPos = 1;
    //    }
    bFlag = 0; //reset flags for the next turn
    aFlag = 0; //reset flags for the next turn
  }
  else if (reading == B00001000) aFlag = 1; //signal that we're expecting pinA to signal the transition to detent from free rotation
  sei(); //restart interrupts
}


void loop() {

  analogWrite(fan, 200);
  // Get temperature event and print its value.
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  temp = round(event.temperature);
  //  Serial.println(temp);



  temp_tens = temp / 10;
  temp_ones = temp - temp_tens * 10;

  tF = temp_tens;
  tS = temp_ones;

  //  char c = '0' + tF;
  //  char c2 = '0' + tS;


  if (temp_tens == 0) {
    tF = 0x003F;
  } else if (temp_tens == 1) {
    tF = 0x0006;
  } else if (temp_tens == 2) {
    tF = 0x00DB;
  } else if (temp_tens == 3) {
    tF = 0x00CF;
  } else if (temp_tens == 4) {
    tF = 0x00E6;
  } else if (temp_tens == 5) {
    tF = 0x00ED;
  } else if (temp_tens == 6) {
    tF = 0x00FD;
  } else if (temp_tens == 7) {
    tF = 0x0027;
  } else if (temp_tens == 8) {
    tF = 0x00FF;
  } else if (temp_tens == 9) {
    tF = 0x00EF;
  }

  if (temp_ones == 0) {
    tS = 0x003F;
  } else if (temp_ones == 1) {
    tS = 0x0006;
  } else if (temp_ones == 2) {
    tS = 0x00DB;
  } else if (temp_ones == 3) {
    tS = 0x00CF;
  } else if (temp_ones == 4) {
    tS = 0x00E6;
  } else if (temp_ones == 5) {
    tS = 0x00ED;
  } else if (temp_ones == 6) {
    tS = 0x00FD;
  } else if (temp_ones == 7) {
    tS = 0x0027;
  } else if (temp_ones == 8) {
    tS = 0x00FF;
  } else if (temp_ones == 9) {
    tS = 0x00EF;
  }

  alpha4.writeDigitRaw(2, tF);
  alpha4.writeDigitRaw(3, tS);

  alpha4.writeDisplay();

  if (oldEncPos != encoderPos) {

    //        Serial.println(encoderPos);

    tens = encoderPos / 10;
    ones = encoderPos - tens * 10;

    if (tens == 0) {
      nF = 0x003F;
    } else if (tens == 1) {
      nF = 0x0006;
    } else if (tens == 2) {
      nF = 0x00DB;
    } else if (tens == 3) {
      nF = 0x00CF;
    } else if (tens == 4) {
      nF = 0x00E6;
    } else if (tens == 5) {
      nF = 0x00ED;
    } else if (tens == 6) {
      nF = 0x00FD;
    } else if (tens == 7) {
      nF = 0x0027;
    } else if (tens == 8) {
      nF = 0x00FF;
    } else if (tens == 9) {
      nF = 0x00EF;
    } else {
      nF = 0x003F;
    }

    if (ones == 0) {
      nS = 0x003F;
    } else if (ones == 1) {
      nS = 0x0006;
    } else if (ones == 2) {
      nS = 0x00DB;
    } else if (ones == 3) {
      nS = 0x00CF;
    } else if (ones == 4) {
      nS = 0x00E6;
    } else if (ones == 5) {
      nS = 0x00ED;
    } else if (ones == 6) {
      nS = 0x00FD;
    } else if (ones == 7) {
      nS = 0x0027;
    } else if (ones == 8) {
      nS = 0x00FF;
    } else if (ones == 9) {
      nS = 0x00EF;
    } else {
      nS = 0x003F;
    }

    alpha4.writeDigitRaw(0, nF);
    alpha4.writeDigitRaw(1, nS);



    //    oldEncPos = encoderPos;


  }

  alpha4.writeDisplay();
  delay(20);

  if (temp == encoderPos) {
    analogWrite(mosPin, 75);
    heat = 75;
  } else if ( temp == (encoderPos - 1)) {
    analogWrite(mosPin, 80);
    heat = 80;
  } else if ( temp == (encoderPos - 2)) {
    analogWrite(mosPin, 100);
    heat = 100;
  } else if ( temp == (encoderPos - 3)) {
    analogWrite(mosPin, 130);
    heat = 130;
  } else if ( temp == (encoderPos - 4)) {
    analogWrite(mosPin, 150);
    heat = 150;
  } else if ( temp == (encoderPos - 5)) {
    analogWrite(mosPin, 200);
    heat = 200;
  }   else if ( temp <= (encoderPos - 6)) {
    analogWrite(mosPin, 255);
    heat = 255;
  } else if ( temp > encoderPos) {
    analogWrite(mosPin, 0);
    heat = 0;
  }

  Serial.println(heat);



}

