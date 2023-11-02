#include <FastLED.h>  // header file
//==============================================================================================================================
#define NUM_LEDS 101  // number of led present in your strip
#define DATA_PIN 3    // digital pin of your arduino
bool startLED = true;
CRGB leds[NUM_LEDS];  // Make this global to edit anywhere

// int r = 0;
// int g = 0;
// int b = 0;
void setup() {
  delay(3000); //This apparently adds some safety
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B, DATA_PIN, BRG>(leds, NUM_LEDS);
  //Serial.begin(9600);
  //Serial.println("msg")
  // leds[0].setRGB(255,0,0);
  // FastLED.show();
  Serial.begin(9600);
}

//A collection of short LED patterns, as an array, that can be retrieved from the main loop and used to intoduce new pulses into the sequence
//It will now start a pattern by adding the leading part to the first position on the strip, shifting all leds up and repeating with the next part of the pattern
//==============================================================================================================================
int patterns(int pattern) {
  //Example pattern int p1[3][3] = {{255,0,0},{0,255,0},{0,0,255}} Can be used as a simple R-G-B pulse
  int p1[3][3] = { { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 } };                               //RGB
  int p2[3][3] = { { 0, 255, 0 }, { 0, 0, 255 }, { 255, 0, 0 } };                               //GBR
  int p3[3][3] = { { 0, 0, 255 }, { 0, 255, 0 }, { 255, 0, 0 } };                               //BRG
  int p4[5][3] = { { 255, 0, 0 }, { 200, 0, 0 }, { 150, 0, 0 }, { 100, 0, 0 }, { 50, 0, 0 } };  //Fading red

  //Serial << "{" << p1[0][0] << "}" ;
  return patterns[pattern];
}

//Takes in the current status of leds CRGB array and shift it up by 1, outputs array new leds array to show later
//==============================================================================================================================
void shiftUp() {

  //FastLED.show();
  //delay(5000);
  
  //Start from the end of the array, make the last one equal to the one below and so on
  for (int i = NUM_LEDS; i > 0; i--) {
    //The first LED doesnt have a predecessor, and therefore is turned off
    leds[i] = leds[i - 1];
  }

  leds[0] = CRGB::Black;
  delay(5); //Added this to hopefully mitigate issue of this function somehow skipping timing logic checks in main loop
}

//Grab one of the patterns and shift it up until it is completely on the strip
//Requires: 
//  Pattern number
//  Length of pattern
//==============================================================================================================================


const long moveuptime = 3000;
const long addnewledtime = 10000;
unsigned long previousMillis1 = 0;  // will store last time LED was updated
unsigned long previousMillis2 = 0;  // will store last time LED was updated
//MAIN FUNCTION
//==============================================================================================================================

void loop() {

    // if (startLED){
    //     leds[0].setRGB(255,0,0);
    //     FastLED.show();
    //     Serial.print("2. startLED = ");
    //     Serial.println(startLED);
    //     startLED = false; // Set it to true only if it was false
    // }

    // unsigned long currentMillis = millis();

    //Add new LED
    EVERY_N_MILLISECONDS(3000){
      // leds[0].setRGB(255,0,0);
      Serial.println("Adding new LED");
      FastLED.show();
    }
  //   if (currentMillis - previousMillis1 >= addnewledtime) {
  //       Serial.print("add led current millis = ");
  //       Serial.println(currentMillis);
  //       Serial.print("add led prev millis = ");
  //       Serial.println(previousMillis1);
  //   // save the last time you blinked the LED
  //     previousMillis1 = currentMillis;
  //   //plonk a new led down - this will be replaced with add pattern
  //     // leds[0].setRGB(255,0,0);
  // } 

  //shiftup by one
  EVERY_N_MILLISECONDS(1000){
    shiftUp();
    FastLED.show();
    Serial.println("Shifting up");
  }
//     if (currentMillis - previousMillis2 >= moveuptime) {
//     // save the last time you blinked the LED
//         // Serial.print("shiftup current millis = ");
//         // Serial.println(currentMillis);
//         // Serial.print("shiftup prev millis = ");
//         // Serial.println(previousMillis2);
//     previousMillis2 = currentMillis;
//     shiftUp();
// } 

    
}

  //   unsigned long currentMillis = millis();
  //   if (currentMillis - previousMillis >= interval2) {
  //   // save the last time you blinked the LED
  //   previousMillis = currentMillis;
  //   //plonk a new led down - this will be replaced with add pattern
  //   // leds[0].setRGB(255,0,0);
  //   // FastLED.show();
  // } 
  // else if(currentMillis - previousMillis >= interval1) {

  // }
  // else{

  // }
  // delay(250);}
  
  

  // if (currentMillis - previousMillis >= interval1) {
  //   shiftUp();
  // }




  //Every 3rd shift up add a new pattern
  

  // //To test the pulse mechanism
  // leds[0].setRGB(255,0,0); //R+G

  // for (int i = 0; i <= NUM_LEDS; i++) {
  //   FastLED.show();
  //   shiftUp();
  //   delay(30);
  // }
  // leds[0].setRGB(0, 0, 0);
  // FastLED.show();
//} 


//==============================================================================================================================
//Sequence of shifting leds up
//1010
//   ^
//1011
//  ^
//1001
// ^
//1101
//^
//0101
//The when the pointer is in the 0th position (first led in strip) it must 'manually' write 0 to it as there's no value beyond it




void add_pattern(int pattern_number) {
  
  //For testing purposes use this as a plac
  int pattern[3][3] = { { 255, 0, 0 }, { 0, 255, 0 }, { 0, 0, 255 } };
  int length = sizeof(pattern)/sizeof(pattern[0]); //length calculation
  
  //For now just have it add a R-G-B pattern
  for(int i; i < length; i++){
    //Move everything up by one first
    
    //Add the next colour to the strip and carry on until no more is left
    leds[0].setRGB(pattern[i,0], pattern[i,1], pattern[i,2]);
    FastLED.show();
    shiftUp();
  }
}
