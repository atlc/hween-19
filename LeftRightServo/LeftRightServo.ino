#include <Servo.h>
#include <Stepper.h>

#define L_BUTT_PIN A0
#define R_BUTT_PIN A1
#define DOWN_BUTT A2
#define UP_BUTT A3
#define SERVO_PIN 6
#define STP_IN_1 13
#define STP_IN_2 12
#define STP_IN_3 11
#define STP_IN_4 10

const float stepsPerRevolution = 64;
const float stepperGearReduction = 64;
const float STEPS = stepsPerRevolution * stepperGearReduction;

Servo servo;
int servoAngle = 90;
int leftButtState = 0;
int rightButtState = 0;

Stepper stepper(stepsPerRevolution, STP_IN_1, STP_IN_3, STP_IN_2, STP_IN_4);
int downButtState = 0;
int upButtState = 0;
int stepCount = 0;

void setup() {
  servo.attach(SERVO_PIN);
  stepper.setSpeed(2500); // Rotations per minute
  pinMode(L_BUTT_PIN, INPUT);
  pinMode(R_BUTT_PIN, INPUT);
  pinMode(DOWN_BUTT, INPUT);
  pinMode(UP_BUTT, INPUT);
  Serial.begin(9600);
}

void loop() {
  evaluateMotors();
  
}

static void evaluateMotors() {
  leftButtState = analogRead(L_BUTT_PIN);
  rightButtState = analogRead(R_BUTT_PIN);
  downButtState = analogRead(DOWN_BUTT);
  upButtState = analogRead(UP_BUTT);
  
  if (rightButtState > 900 && leftButtState < 500 && servoAngle < 180) {
    servoAngle += 3;
  } else if (leftButtState > 900 && servoAngle > 0) {
    servoAngle -= 3;
  }
  
  servo.write(servoAngle);
  
  if (downButtState > 900 && upButtState < 150) {
    stepper.step(-128);
  }
  
  if(upButtState > 900 && downButtState < 150) {
    stepper.step(128);
  }  
 
  Serial.print("Down:  "); Serial.print(downButtState); Serial.print(";     Up:  "); Serial.println(upButtState);

  Serial.print("rB.ST:  "); Serial.print(rightButtState); Serial.print(";     lB.ST:  "); Serial.print(leftButtState); Serial.print(";     Angle:  "); Serial.println(servoAngle);
}
