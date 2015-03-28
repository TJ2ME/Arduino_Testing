// pin assignments
int LED = 13; 
int LDR = 0;

// global variables
int LDRvoltage;        // placeholder for voltage of LDR 
int regLDRvoltage;     // placeholder for original voltage of LDR during set up time
int threshold = 100;   // the threshold for the difference between the LDRvoltage and the regLDRvoltage for when to change the output
                       // of the LED

void setup() {
  // pin assignments
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);
  
  // sets the regular LDR voltage 
  regLDRvoltage = analogRead(LDR);
}

void loop() {
  LDRvoltage = analogRead(LDR);
  if( (regLDRvoltage - LDRvoltage) > threshold ){
    digitalWrite(LED, HIGH);
  }
  else{
    digitalWrite(LED, LOW);
  }
    
}
