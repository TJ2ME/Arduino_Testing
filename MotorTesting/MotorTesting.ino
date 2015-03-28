#include <Servo.h>

Servo servoOne;

// Function Prototype(s)
void twistServo(Servo servoMotor, int delayVal);

void setup() {
  // put your setup code here, to run once:
  servoOne.attach(11);
    
  // Sets the servo to a default of 0 degrees
  servoOne.write(0);
  delay(3000);
}

void loop() {
  twistServo(servoOne, 500, 30, true);
  twistServo(servoOne, 500, 30, false); 
}

/**
 * @param servoMotor - the servoMotor we are using
 * @param delayVal - the delay per twist in miliseconds
 * @param angleIncrement - the angle by which the servo twists for each twist
 * @param up - do we want the servo turning from 0 to 180, or 180 to 0? up = true for the former
*/
void twistServo(Servo servoMotor, int delayVal, int angleIncrement, bool up){
  int numOfIncrements = 180 / angleIncrement;
  
  int i;
  
  // When we want servo to turn from 0 to 180
  if(up){
    for (i = 1; i <= numOfIncrements; i++){
      servoMotor.write(angleIncrement*i);
      delay(delayVal);
    }
  }
  
  // When we want servo to turn from 180 to 0
  else{
    for (i = numOfIncrements; i >= 0; i--){
      servoMotor.write(angleIncrement*i);
      delay(delayVal);
    }
  }
}
