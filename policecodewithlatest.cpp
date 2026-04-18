// ================= PIN CONFIG =================

// ----- RED LEDs (6) -----
int red[]  = {6,7,8,9,10,11};

// ----- BLUE LEDs (6) -----
// A4 replaced with 0 (RX pin)
int blue[] = {A1,A2,A3,A4,12,13};

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
    case 0: cruise(); break;
    case 1: lightbarSingle(); break;
    case 2: lightbarDouble(); break;
    case 3: lightbarTriple(); break;
    case 4: americanBurst(); break;
    case 5: alternatingRapid(); break;
    case 6: progressiveSweep(); break;
    case 7: pursuitChase(); break;
    case 8: fullStrobe(); break;
  }
}


// ================= BUTTON =================
void checkButton(){
  int reading = digitalRead(buttonPin);

  if(reading == LOW && lastButtonState == HIGH){
    mode++;
    if(mode > 8) mode = 0; // fixed (you had 9 but only 0–8 modes)
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

void redSide(){
  for(int i=0;i<6;i++){
    digitalWrite(red[i],HIGH);
    digitalWrite(blue[i],LOW);
  }
  digitalWrite(frontLeft,LOW);
  digitalWrite(rearLeft,LOW);
  digitalWrite(frontRight,HIGH);
  digitalWrite(rearRight,HIGH);
}

void blueSide(){
  for(int i=0;i<6;i++){
    digitalWrite(blue[i],HIGH);
    digitalWrite(red[i],LOW);
  }
  digitalWrite(frontRight,LOW);
  digitalWrite(rearRight,HIGH);
  digitalWrite(frontLeft,HIGH);
  digitalWrite(rearLeft,HIGH);
}

void redSideAlternate(){
  for(int i=0;i<6;i++){
    digitalWrite(red[i],HIGH);
    digitalWrite(blue[i],LOW);
  }
  digitalWrite(frontLeft,HIGH);
  digitalWrite(frontRight,LOW);
  digitalWrite(rearLeft,LOW);
  digitalWrite(rearRight,HIGH);
}

void blueSideAlternate(){
  for(int i=0;i<6;i++){
    digitalWrite(blue[i],HIGH);
    digitalWrite(red[i],LOW);
  }
  digitalWrite(frontLeft,LOW);
  digitalWrite(frontRight,HIGH);
  digitalWrite(rearLeft,HIGH);
  digitalWrite(rearRight,LOW);
}

// ================= MODES =================

// 0 – Cruise
void cruise(){
  allOff();
  digitalWrite(frontLeft,HIGH);
  digitalWrite(frontRight,HIGH);
  digitalWrite(rearLeft,HIGH);
  digitalWrite(rearRight,HIGH);
  delay(100);
}

// 1 – Single
void lightbarSingle(){
  redSideAlternate(); delay(1000); allOff(); delay(80);
  blueSideAlternate(); delay(1000); allOff(); delay(80);
}

// 2 – Double
void lightbarDouble(){
  for(int i=0;i<2;i++){
    redSideAlternate(); delay(100); allOff(); delay(70);
  }
  for(int i=0;i<2;i++){
    blueSideAlternate(); delay(100); allOff(); delay(70);
  }
}

// 3 – Triple
void lightbarTriple(){
  for(int i=0;i<3;i++){
    redSideAlternate(); delay(90); allOff(); delay(60);
  }
  for(int i=0;i<3;i++){
    blueSideAlternate(); delay(90); allOff(); delay(60);
  }
}

// 4 – American 2-2 Burst
void americanBurst(){
  for(int i=0;i<2;i++){
    redSide(); delay(80); allOff(); delay(50);
  }
  delay(120);
  for(int i=0;i<2;i++){
    blueSide(); delay(80); allOff(); delay(50);
  }
  delay(150);
}

// 5 – Alternating Rapid
void alternatingRapid(){
  redSide(); delay(500);
  blueSide(); delay(500);
}

// 6 – Progressive Sweep
void progressiveSweep(){
  allOff();
  for(int i=0;i<6;i++){
    digitalWrite(red[i],HIGH);
    digitalWrite(frontLeft,HIGH);
    digitalWrite(rearLeft,HIGH);
    delay(60);
  }
  allOff();
  for(int i=5;i>=0;i--){
    digitalWrite(blue[i],HIGH);
    digitalWrite(frontRight,HIGH);
    digitalWrite(rearRight,HIGH);
    delay(60);
  }
}

// 7 – Pursuit Chase
void pursuitChase(){
  for(int i=0;i<6;i++){
    allOff();
    digitalWrite(red[i],HIGH);
    digitalWrite(frontLeft,HIGH);
    digitalWrite(rearLeft,HIGH);
    delay(70);
  }
  for(int i=0;i<6;i++){
    allOff();
    digitalWrite(blue[i],HIGH);
    digitalWrite(frontRight,HIGH);
    digitalWrite(rearRight,HIGH);
    delay(70);
  }
}


// 8 – Full Power Strobe
void fullStrobe(){
  for(int i=0;i<6;i++){
    digitalWrite(red[i],HIGH);
    digitalWrite(blue[i],HIGH);
  }
  digitalWrite(frontLeft,HIGH);
  digitalWrite(frontRight,HIGH);
  digitalWrite(rearLeft,HIGH);
  digitalWrite(rearRight,HIGH);
  delay(500);
  allOff();
  delay(500);
}