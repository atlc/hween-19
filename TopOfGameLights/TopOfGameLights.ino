#include <Adafruit_NeoPixel.h>

#define PIN    7
#define N_LEDS 60

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

#define WHITE strip.Color(225,192,80)

void setup() {
  strip.begin();
}

void loop() {
  chase();
  flash();
  flash();
}

static void chase() {
  for(int i=0; i<N_LEDS+8; i++) {
    for(int j=0; j<8; j++) {
      strip.setPixelColor(i-j, WHITE); // Draw new pixel
      strip.setPixelColor(i-8, 0); // Erase pixel a few steps back
      strip.show();
    }
    delay(15);
  }
  delay(350);
}

static void flash() {
  for (int i=0; i<N_LEDS; i++) {
    strip.setPixelColor(i, WHITE);
  }
  strip.show();
  delay(256);
  
  for (int i=0; i<N_LEDS; i++) {
    strip.setPixelColor(i, 0);
  }
  strip.show();
  delay(128);
}
