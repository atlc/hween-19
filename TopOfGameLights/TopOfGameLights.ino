#include <Adafruit_NeoPixel.h>
#include <Servo.h>

#define R_BUTT_PIN A0
#define SERVO_PIN 6
#define NEO_PIN 7
#define N_LEDS 60

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, NEO_PIN, NEO_GRB + NEO_KHZ800);

// #define WHITE strip.Color(225,192,80)
#define WHITE strip.Color(22,19,8)

Servo servo;
int servoCounter = 0;
int rightButtState = 0;

void setup() {
  Serial.begin(9600);
  strip.begin();
  servo.attach(SERVO_PIN);
  pinMode(R_BUTT_PIN, INPUT);
  chase();
  flash();
}

void loop() {
  rightButtState = digitalRead(R_BUTT_PIN);
  
  if (rightButtState == HIGH) {
    servoCounter++;
    Serial.print("Button hit:     ");
    Serial.println(servoCounter);
    delay(250); 
  }
  
  if (servoCounter == 0) {
    servo.write(0);
  } else if (servoCounter == 1) {
    servo.write(60);
  } else if (servoCounter == 2) {
    servo.write(120);
  } else if (servoCounter == 3) {
    servo.write(179);
  } else {
    servoCounter = 0;
  }
//  rainbow(128);
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

/*
void rainbow(uint8_t wait) {
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, Wheel((i*1+j) & 255));
    }
    strip.show();
    delay(wait);
  }
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
*/
