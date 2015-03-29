/** MAIN FUNCTIONS TO USE
 *  soundAlarm()                    -- sounds the Mario theme song alarm
 *  detectLight()                   -- activates the photo-resistor (light detection); turns on/off gLEDa depending on external light intensity
 *  closeGarageDoor(Servo motor)    -- closes the garage door
 *  openGarageDoor(Servo motor)     -- opens the garage door
 **/ 

 
// --------------------- PRE-PROCESSORS ---------------------
// FOR GARAGE DOOR
#include <Servo.h>

// FOR ALARM
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44  
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
 
#define melodyPin 3


// --------------------- COMPONENTS AND PIN ASSIGNMENTS ---------------------
// FOR GARAGE DOOR
Servo motor;
int motorPin = 11;        // has to be PWM

// FOR LIGHT DETECTOR
int gLEDa = 13;
int LDR = 0;              // as in A0; has to be analog 

// FOR ALARM
int buzzer = 3;
int rLEDa = 12;
 

// --------------------- FUNCTION PROTOTYPES ---------------------
// FOR GARAGE DOOR
void twistServo(Servo servoMotor, int delayVal, int angleIncrement, bool up);
void closeGarageDoor(Servo servoMotor);
void openGarageDoor(Servo servoMotor);

// FOR LIGHT DETECTOR
void detectLight();

// FOR ALARM
void sing(int s);
void buzz(int targetPin, long frequency, long length);
void soundAlarm();


// --------------------- CONSTANTS AND GLOBAL VARIABLES ---------------------

// FOR LIGHT DETECTOR
int LDRvoltage;           // placeholder for voltage of LDR 
int regLDRvoltage;        // placeholder for original voltage of LDR during set up time
int threshold = 100;      // the threshold for the difference between the LDRvoltage and the regLDRvoltage for when to change the output
                          // of the LED
 
// FOR ALARM
int melody[] = {
  NOTE_E7, NOTE_E7, 0, NOTE_E7,
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0,
 
  NOTE_C7, 0, 0, NOTE_G6,
  0, 0, NOTE_E6, 0,
  0, NOTE_A6, 0, NOTE_B6,
  0, NOTE_AS6, NOTE_A6, 0,
 
  NOTE_G6, NOTE_E7, NOTE_G7,
  NOTE_A7, 0, NOTE_F7, NOTE_G7,
  0, NOTE_E7, 0, NOTE_C7,
  NOTE_D7, NOTE_B6, 0, 0
};
//Mario main them tempo
int tempo[] = {
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
 
  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};
//Underworld melody
int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4,
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4,
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4, NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};
//Underworld tempo
int underworld_tempo[] = {
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  3,
  12, 12, 12, 12,
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18, 18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

int song = 0;
 
// FOR SERIAL
int incomingInput;


// --------------------- SET UP --------------------- 

void setup(){
  Serial.begin(9600);
  
  // Attaches the servo to an assigned pin; sets the servo to an initial configuration of 0 degrees
  motor.attach(motorPin);
  motor.write(0);
  
  // Pin assignments for LightDetector
  pinMode(gLEDa, OUTPUT);
  pinMode(LDR, INPUT);
  
  // sets the base (initial) LDR voltage 
  regLDRvoltage = analogRead(LDR);
  
  // Pin assignments for Alarm
  pinMode(buzzer, OUTPUT); 
  pinMode(rLEDa, OUTPUT);   
}
 
 
// --------------------- LOOP --------------------- 

void loop(){
   while(Serial.available() == 0);
   
   incomingInput = Serial.read() - '0';
   
   switch(incomingInput){
        case 1:
        openGarageDoor(motor);
        break;
        
        case 2:
        closeGarageDoor(motor);
        break;
        
        case 3:
        detectLight();
        digitalWrite(gLEDa, HIGH);
        break;
        
        case 4:
        soundAlarm();
        break;
        
        default:
        Serial.println("Error: invalid input.");
        break;
   }
}


// --------------------- GARAGE DOOR FUNCTION IMPLEMENTATIONS ---------------------

/**
 * @param servoMotor - the servoMotor we are using
 * @param delayVal - the delay per twist in milliseconds
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


// --------------------- LIGHT DETECTOR FUNCTION IMPLEMENTATIONS ---------------------

void detectLight(){
  int counter;
  LDRvoltage = analogRead(LDR);
  while(counter < 10){
    if( (regLDRvoltage - LDRvoltage) > threshold ){
      digitalWrite(gLEDa, HIGH);
      counter++;
    }
    else{
      digitalWrite(gLEDa, LOW);
      counter++;
    }  
  }  
}



// --------------------- ALARM FUNCTION IMPLEMENTATIONS ---------------------

void sing(int s) {
  // iterate over the notes of the melody:
  song = s;
  if (song == 2) {
    
    int size = sizeof(underworld_melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {      
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / underworld_tempo[thisNote];
 
      buzz(melodyPin, underworld_melody[thisNote], noteDuration);
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
 
      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);
 
    }
 
  } else {
 
    int size = sizeof(melody) / sizeof(int);
    for (int thisNote = 0; thisNote < size; thisNote++) {
 
      // to calculate the note duration, take one second
      // divided by the note type.
      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
      int noteDuration = 1000 / tempo[thisNote];
 
      buzz(melodyPin, melody[thisNote], noteDuration);
 
      // to distinguish the notes, set a minimum time between them.
      // the note's duration + 30% seems to work well:
      int pauseBetweenNotes = noteDuration * 1.30;
      delay(pauseBetweenNotes);
 
      // stop the tone playing:
      buzz(melodyPin, 0, noteDuration);
 
    }
  }
}
 
void buzz(int targetPin, long frequency, long length) {
  digitalWrite(rLEDa, HIGH);
  long delayValue = 1000000 / frequency / 2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length / 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to
  //// get the total number of cycles to produce
  for (long i = 0; i < numCycles; i++) { // for the calculated length of time...
    digitalWrite(targetPin, HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin, LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  } 
  
  digitalWrite(rLEDa, LOW);
}

void soundAlarm(){
   sing(1);
}

