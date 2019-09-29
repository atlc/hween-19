#include <Servo.h>

#define L_BUTT_PIN A0
#define R_BUTT_PIN A1
#define SERVO_PIN 6

Servo servo;
int servoAngle = 90;
int leftButtState = 0;
int rightButtState = 0;

void setup() {
  Serial.begin(9600);
  servo.attach(SERVO_PIN);
  pinMode(L_BUTT_PIN, INPUT);
  pinMode(R_BUTT_PIN, INPUT);
}

void loop() {  
  evaluateMotors();
  delay(50);
}

static void evaluateMotors() {
  slideServo();
}

static void slideServo() {
  leftButtState = analogRead(L_BUTT_PIN);
  rightButtState = analogRead(R_BUTT_PIN);
  
  if (rightButtState > 900 && leftButtState < 500 && servoAngle < 180) {
    servoAngle+= 3;
  } else if (leftButtState > 900 && servoAngle > 0) {
    servoAngle-= 3;
  }

  Serial.print("rB.ST:  "); Serial.print(rightButtState); Serial.print(";     lB.ST:  "); Serial.print(leftButtState); Serial.print(";     Angle:  "); Serial.println(servoAngle);
  servo.write(servoAngle); 
}
