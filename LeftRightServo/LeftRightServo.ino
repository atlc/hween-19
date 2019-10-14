#include <Servo.h>

/* Setup for the arcade joystick */
#define L_BUTT_PIN A0
#define R_BUTT_PIN A1
#define DOWN_BUTT A2
#define UP_BUTT A3

int leftButtState = 0;
int rightButtState = 0;
int downButtState = 0;
int upButtState = 0;

/* Setup for the servo motor */
const int SERVO_PIN = 6;
Servo servo;
int servoAngle = 90;


/* Setup for the stepper motor */
const int STEPPER_STEP_PIN = 3;
const int STEPPER_DIR_PIN = 4;

void setup() {
  servo.attach(SERVO_PIN);
  pinMode(L_BUTT_PIN, INPUT);
  pinMode(R_BUTT_PIN, INPUT);
  pinMode(DOWN_BUTT, INPUT);
  pinMode(UP_BUTT, INPUT);
  pinMode(STEPPER_STEP_PIN, OUTPUT);
  pinMode(STEPPER_DIR_PIN, OUTPUT);
  Serial.begin(9600); // For logging & monitoring
}

void loop() {
  evaluateMotors();
 
}

static void evaluateMotors() {
  leftButtState = analogRead(L_BUTT_PIN);
  rightButtState = analogRead(R_BUTT_PIN);
  downButtState = analogRead(DOWN_BUTT);
  upButtState = analogRead(UP_BUTT);
  
  if (rightButtState > 900 && leftButtState < 500 && servoAngle < 120) {
    servoAngle += 3;
  } else if (leftButtState > 900 && servoAngle > 40) {
    servoAngle -= 3;
  }
  
  servo.write(servoAngle);
  
  if (downButtState > 900 && upButtState < 150) {
    digitalWrite(STEPPER_DIR_PIN, HIGH);
    for(int x = 0; x < 400; x++) {
      digitalWrite(STEPPER_STEP_PIN, HIGH); 
      delayMicroseconds(500); 
      digitalWrite(STEPPER_STEP_PIN, LOW); 
      delayMicroseconds(500); 
    }
  }
  
  if(upButtState > 900 && downButtState < 150) {
    digitalWrite(STEPPER_DIR_PIN, LOW);
    for(int x = 0; x < 400; x++) {
      digitalWrite(STEPPER_STEP_PIN, HIGH); 
      delayMicroseconds(500); 
      digitalWrite(STEPPER_STEP_PIN, LOW); 
      delayMicroseconds(500); 
    }
  }  
 
  Serial.print("Down:  "); Serial.print(downButtState); Serial.print(";     Up:  "); Serial.println(upButtState);

  Serial.print("Right:  "); Serial.print(rightButtState); Serial.print(";     Left:  "); Serial.print(leftButtState); Serial.print(";     Angle:  "); Serial.println(servoAngle);
}
