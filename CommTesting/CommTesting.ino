// Learning Serial Communication part 2
// Reading the output of an LED light

int gLEDpin = 13;
int rLEDpin = 8;
int incomingInput;

void setup() {
  Serial.begin(9600);
  pinMode(gLEDpin, OUTPUT);
  pinMode(rLEDpin, OUTPUT);
  //establishContact();
}

void loop() {
  while(Serial.available() == 0);
  
  incomingInput = Serial.read() - '0';
  //incomingInput = Serial.readString();
  Serial.println(incomingInput);
  
  if (incomingInput == 1){
    digitalWrite(gLEDpin, HIGH);
    digitalWrite(rLEDpin, LOW);
  }
  else if (incomingInput == 0){
    digitalWrite(gLEDpin, LOW);
    digitalWrite(rLEDpin, LOW);
  }
  else{
    digitalWrite(rLEDpin, HIGH);
  }
}

void establishContact(){
  while (Serial.available() <= 0){
    Serial.println("I AM ALIVE");
    delay(300);
  } 
}
