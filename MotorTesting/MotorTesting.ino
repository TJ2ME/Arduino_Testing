#include <Servo.h>

Servo servoOne;

// Function Prototype(s)
void twistServo(Servo servoMotor, int delayVal, int angleIncrement, bool up);
void closeGarageDoor(Servo servoMotor);
void openGarageDoor(Servo servoMotor);

void setup() {
  // put your setup code here, to run once:
  servoOne.attach(11);
    
  // Sets the servo to a default of 0 degrees
  servoOne.write(0);
  delay(3000);
}

void loop() {
  // Twist servo motor from 0 to 180
  openGarageDoor(servoOne);
  delay(2000);
  
  // Twist servo motor from 180 to 0
  closeGarageDoor(servoOne);
  delay(2000); 
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

void closeGarageDoor(Servo servoMotor){
   twistServo(servoMotor, 250, 30, false); 
}

void openGarageDoor(Servo servoMotor){
   twistServo(servoMotor, 250, 30, true);
}
