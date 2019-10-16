#include <Adafruit_NeoPixel.h>

#define NEO_PIN 8
#define BACKLIGHT 7
#define N_LEDS 60

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS*2, NEO_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel backlight = Adafruit_NeoPixel(N_LEDS, BACKLIGHT, NEO_GRB + NEO_KHZ800);

// #define WHITE strip.Color(225,192,80)
#define WHITE strip.Color(60,50,28)
#define BACKLIGHT_WHITE strip.Color(60,60,60)

void setup() {
  Serial.begin(9600);
  strip.begin();
  backlight.begin();
}

void loop() {
  backlightOn();
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

static void backlightOn() {
   for(int i=0; i<N_LEDS; i++) {
    backlight.setPixelColor(i, BACKLIGHT_WHITE);
    backlight.show();
  } 
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
  
  for (int i=0; i<N_LEDS; i++) {
    strip.setPixelColor(i, 0);
  }
  strip.show();
  delay(80);
}

void rainbow(uint8_t wait) {
  backlight.clear();
  backlight.show();
  uint16_t i, j;
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

