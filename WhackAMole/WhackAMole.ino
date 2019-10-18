#include <Adafruit_NeoPixel.h>
#include "LedControl.h"
#include "binary.h"

LedControl lc=LedControl(12,11,10,4);  // DIN on 12; CLK on 11; CS on 10; 4 LED matrixes

const byte OUCH[][8] = {
{
  B01100110,
  B01100110,
  B01100110,
  B01111110,
  B01111110,
  B01100110,
  B01100110,
  B01100110
},{
  B00011110,
  B00111110,
  B01100000,
  B01100000,
  B01100000,
  B01100000,
  B00111110,
  B00011110
},{
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B01111110,
  B00111100
},{
  B00111100,
  B01111110,
  B01100110,
  B01100110,
  B01100110,
  B01100110,
  B01111110,
  B00111100
}};
const int OUCH_LEN = sizeof(OUCH)/8;

#define NEO_PIN 8
#define N_LEDS 60

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, NEO_PIN, NEO_GRB + NEO_KHZ800);
#define WHITE strip.Color(45,40,21)

void setup() {
  int devices=lc.getDeviceCount();
  for(int address=0;address<devices;address++) {
    lc.shutdown(address,false); // Each matrix screen is in power-saving mode on startup
    lc.setIntensity(address,1);
    lc.clearDisplay(address);
  }
  sayOuch();
  strip.begin();
}

void loop() {
  neopixelLoop();
}

static void sayOuch() {
  for (int i=0; i<OUCH_LEN; i++) {
    for (int j=0; j<8; j++) {
      lc.setRow(i,j, OUCH[i][j]);
    }
  }
}



/* NEOPIXELS SECTION */

static void neopixelLoop() {
  chase();
  flash();
  flash();
  delay(150);
  chase();
  flash();
  flash();
  delay(150);
  chase();
  flash();
  flash();
  delay(150);
  rainbow(128); 
}


static void chase() {
  for(int i=0; i<N_LEDS+8; i++) {
    for(int j=0; j<8; j++) {
      strip.setPixelColor(i-j, WHITE); // Draw new pixel
      strip.setPixelColor(i-8, 0); // Erase pixel a few steps back
      strip.show();
    }
    delay(8);
  }
  delay(350);
}

static void flash() {
  for (int i=0; i<N_LEDS; i++) {
    strip.setPixelColor(i, WHITE);
  }
  strip.show();
  delay(175);
  strip.clear();
  strip.show();
  delay(80);
}

void rainbow(uint8_t wait) {
  uint16_t i = 0;
  uint16_t j = 0;
  for(j=0; j<128; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i*1+j) & 255));
    }
    strip.show();
    delay(wait);
  }
  strip.clear();
  strip.show();
}


// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } 
  else if(WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } 
  else {
    WheelPos -= 170;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
}

