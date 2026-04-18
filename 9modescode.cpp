// ================= PIN CONFIG =================
MODE LIST

0  – Blackout
1  – Lightbar Single
2  – Lightbar Double
3  – Lightbar Triple
4  – American Patrol (2-2 Burst)
5  – Cruise Lights
6  – Progressive Sweep
7  – Pursuit Chase
8  – Split Phase
9  – Full Power Strobe


// ----- RED LEDs (Left Half) -----
int red[]  = {6,7,10,11,12,13};

// ----- BLUE LEDs (Right Half) -----
int blue[] = {A1,A2,A3,A4,8,9};

// ----- FRONT / REAR -----
int frontLeft  = 2;
int frontRight = 3;
int rearLeft   = 4;
int rearRight  = 5;

// ----- BUTTON -----
int buttonPin = A0;

int mode = 0;
int lastButtonState = HIGH;


// ================= SETUP =================
void setup() {

  for(int i=0;i<6;i++){
    pinMode(red[i],OUTPUT);
    pinMode(blue[i],OUTPUT);
  }

  pinMode(frontLeft,OUTPUT);
  pinMode(frontRight,OUTPUT);
  pinMode(rearLeft,OUTPUT);
  pinMode(rearRight,OUTPUT);

  pinMode(buttonPin, INPUT_PULLUP);
}


// ================= LOOP =================
void loop() {

  checkButton();

  switch(mode){

    case 0: blackout(); break;
    case 1: lightbarSingle(); break;
    case 2: lightbarDouble(); break;
    case 3: lightbarTriple(); break;
    case 4: americanPatrol(); break;
    case 5: cruise(); break;
    case 6: progressiveSweep(); break;
    case 7: pursuitChase(); break;
    case 8: splitPhase(); break;
    case 9: fullStrobe(); break;
  }
}


// ================= BUTTON =================
void checkButton(){

  int reading = digitalRead(buttonPin);

  if(reading == LOW && lastButtonState == HIGH){
    mode++;
    if(mode > 9) mode = 0;
    delay(250);
  }

  lastButtonState = reading;
}


// ================= COMMON =================

void allOff(){
  for(int i=0;i<6;i++){
    digitalWrite(red[i],LOW);
    digitalWrite(blue[i],LOW);
  }
  digitalWrite(frontLeft,LOW);
  digitalWrite(frontRight,LOW);
  digitalWrite(rearLeft,LOW);
  digitalWrite(rearRight,LOW);
}

void leftBar(){
  for(int i=0;i<3;i++) digitalWrite(red[i],HIGH);
  for(int i=0;i<6;i++) digitalWrite(blue[i],LOW);

  digitalWrite(frontLeft,HIGH);
  digitalWrite(rearLeft,HIGH);
  digitalWrite(frontRight,LOW);
  digitalWrite(rearRight,LOW);
}

void rightBar(){
  for(int i=3;i<6;i++) digitalWrite(blue[i],HIGH);
  for(int i=0;i<6;i++) digitalWrite(red[i],LOW);

  digitalWrite(frontRight,HIGH);
  digitalWrite(rearRight,HIGH);
  digitalWrite(frontLeft,LOW);
  digitalWrite(rearLeft,LOW);
}


// ================= PATTERNS =================

// MODE 0 – Blackout
void blackout(){
  allOff();
  delay(100);
}


// MODE 1 – Lightbar Single
void lightbarSingle(){
  leftBar(); delay(120); allOff(); delay(80);
  rightBar(); delay(120); allOff(); delay(80);
}


// MODE 2 – Lightbar Double
void lightbarDouble(){
  for(int i=0;i<2;i++){
    leftBar(); delay(100); allOff(); delay(60);
  }
  for(int i=0;i<2;i++){
    rightBar(); delay(100); allOff(); delay(60);
  }
}


// MODE 3 – Lightbar Triple
void lightbarTriple(){
  for(int i=0;i<3;i++){
    leftBar(); delay(90); allOff(); delay(60);
  }
  for(int i=0;i<3;i++){
    rightBar(); delay(90); allOff(); delay(60);
  }
}


// MODE 4 – American Patrol 2-2 Burst
void americanPatrol(){

  for(int i=0;i<2;i++){
    leftBar(); delay(80); allOff(); delay(50);
  }

  delay(120);

  for(int i=0;i<2;i++){
    rightBar(); delay(80); allOff(); delay(50);
  }

  delay(180);
}


// MODE 5 – Cruise Lights
void cruise(){
  allOff();
  digitalWrite(frontLeft,HIGH);
  digitalWrite(frontRight,HIGH);
  digitalWrite(rearLeft,HIGH);
  digitalWrite(rearRight,HIGH);
  delay(100);
}


// MODE 6 – Progressive Sweep
void progressiveSweep(){

  for(int i=0;i<3;i++){
    digitalWrite(red[i],HIGH);
    digitalWrite(frontLeft,HIGH);
    digitalWrite(rearLeft,HIGH);
    delay(70);
  }

  allOff();
  delay(70);

  for(int i=3;i<6;i++){
    digitalWrite(blue[i],HIGH);
    digitalWrite(frontRight,HIGH);
    digitalWrite(rearRight,HIGH);
    delay(70);
  }

  allOff();
  delay(70);
}


// MODE 7 – Pursuit Chase
void pursuitChase(){

  for(int i=0;i<3;i++){
    digitalWrite(red[i],HIGH);
    digitalWrite(frontLeft,HIGH);
    digitalWrite(rearLeft,HIGH);
    delay(60);
    digitalWrite(red[i],LOW);
  }

  for(int i=3;i<6;i++){
    digitalWrite(blue[i],HIGH);
    digitalWrite(frontRight,HIGH);
    digitalWrite(rearRight,HIGH);
    delay(60);
    digitalWrite(blue[i],LOW);
  }
}


// MODE 8 – Split Phase
void splitPhase(){
  leftBar(); delay(120); allOff(); delay(60);
  rightBar(); delay(160); allOff(); delay(60);
}


// MODE 9 – Full Power Strobe
void fullStrobe(){

  for(int i=0;i<6;i++){
    digitalWrite(red[i],HIGH);
    digitalWrite(blue[i],HIGH);
  }

  digitalWrite(frontLeft,HIGH);
  digitalWrite(frontRight,HIGH);
  digitalWrite(rearLeft,HIGH);
  digitalWrite(rearRight,HIGH);

  delay(120);
  allOff();
  delay(80);
}
