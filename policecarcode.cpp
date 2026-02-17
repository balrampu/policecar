// ================= PIN GROUPS =================

// Front white (2)
int whiteFront[] = {2, 3};

// Rear red tail (2)
int rearRed[] = {4, 5};

// 🔴 Reds (6)
int reds[] = {6, 7, 10, 11, 12, 13};

// 🔵 Blues (6)
int blues[] = {A1, A2, A3, A4, 8, 9};

// Button
#define BTN A0

// ==============================================

int mode = 0;
int lastBtn = HIGH;
unsigned long lastDebounce = 0;
const unsigned long debounceDelay = 150;

// ================= SETUP =================
void setup() {

  pinMode(BTN, INPUT_PULLUP);

  int pins[] = {
    2,3,4,5,
    6,7,10,11,12,13,
    A1,A2,A3,A4,8,9
  };

  for (int i = 0; i < 16; i++)
    pinMode(pins[i], OUTPUT);

  allOff();
}

// ================= LOOP =================
void loop() {

  handleButton();

  if(mode == 0){
    allOff();
    return;
  }

  baseLights();   // Always ON in every mode

  switch(mode) {

    case 1: steadyWhiteRear(); break;
    case 2: singleAlternate(); break;
    case 3: doubleAlternate(); break;
    case 4: tripleAlternate(); break;
    case 5: fastSweep(); break;
    case 6: fastChase(); break;
    case 7: burstStrobe(); break;
    case 8: chaosPolice(); break;
    case 9: wigWagSplit(); break;
    case 10: quadFlash(); break;
    case 11: sideAttack(); break;
    case 12: machineGun(); break;
  }
}

// ================= BUTTON =================
void handleButton() {

  int reading = digitalRead(BTN);

  if (reading == LOW && lastBtn == HIGH) {
    if (millis() - lastDebounce > debounceDelay) {
      mode++;
      if (mode > 12) mode = 0;
      lastDebounce = millis();
    }
  }

  lastBtn = reading;
}

// ================= BASE LIGHT CONTROL =================

void baseLights() {
  setGroup(whiteFront, 2, HIGH);
  setGroup(rearRed, 2, HIGH);
}

void flickerBase() {
  digitalWrite(whiteFront[0], HIGH);
  digitalWrite(whiteFront[1], LOW);
  digitalWrite(rearRed[0], HIGH);
  digitalWrite(rearRed[1], LOW);
  delay(20);

  digitalWrite(whiteFront[0], LOW);
  digitalWrite(whiteFront[1], HIGH);
  digitalWrite(rearRed[0], LOW);
  digitalWrite(rearRed[1], HIGH);
  delay(20);

  baseLights();
}

// ================= COMMON =================
void allOff() {
  setGroup(whiteFront, 2, LOW);
  setGroup(rearRed, 2, LOW);
  setGroup(reds, 6, LOW);
  setGroup(blues, 6, LOW);
}

// ================= PATTERNS =================

// 1
void steadyWhiteRear() {
  flickerBase();
}

// 2
void singleAlternate() {
  setGroup(reds, 6, HIGH);
  flickerBase();
  delay(100);
  setGroup(reds, 6, LOW);

  setGroup(blues, 6, HIGH);
  flickerBase();
  delay(100);
  setGroup(blues, 6, LOW);
}

// 3
void doubleAlternate() {
  for(int i=0;i<2;i++){
    setGroup(reds,6,HIGH);
    flickerBase();
    delay(70);
    setGroup(reds,6,LOW);
    delay(50);
  }
  for(int i=0;i<2;i++){
    setGroup(blues,6,HIGH);
    flickerBase();
    delay(70);
    setGroup(blues,6,LOW);
    delay(50);
  }
}

// 4
void tripleAlternate() {
  for(int i=0;i<3;i++){
    setGroup(reds,6,HIGH);
    flickerBase();
    delay(60);
    setGroup(reds,6,LOW);
    delay(40);
  }
  for(int i=0;i<3;i++){
    setGroup(blues,6,HIGH);
    flickerBase();
    delay(60);
    setGroup(blues,6,LOW);
    delay(40);
  }
}

// 5
void fastSweep() {
  for(int i=0;i<6;i++){
    digitalWrite(reds[i], HIGH);
    flickerBase();
    delay(40);
    digitalWrite(reds[i], LOW);
  }
  for(int i=0;i<6;i++){
    digitalWrite(blues[i], HIGH);
    flickerBase();
    delay(40);
    digitalWrite(blues[i], LOW);
  }
}

// 6
void fastChase() {
  for(int i=0;i<5;i++){
    digitalWrite(reds[i], HIGH);
    digitalWrite(reds[i+1], HIGH);
    flickerBase();
    delay(60);
    digitalWrite(reds[i], LOW);
    digitalWrite(reds[i+1], LOW);
  }
  for(int i=0;i<5;i++){
    digitalWrite(blues[i], HIGH);
    digitalWrite(blues[i+1], HIGH);
    flickerBase();
    delay(60);
    digitalWrite(blues[i], LOW);
    digitalWrite(blues[i+1], LOW);
  }
}

// 7
void burstStrobe() {
  for(int i=0;i<5;i++){
    setGroup(reds,6,HIGH);
    setGroup(blues,6,HIGH);
    flickerBase();
    delay(50);
    setGroup(reds,6,LOW);
    setGroup(blues,6,LOW);
    delay(50);
  }
}

// 8
void chaosPolice() {
  setGroup(reds,6,HIGH);
  flickerBase();
  delay(70);
  setGroup(blues,6,HIGH);
  flickerBase();
  delay(70);
  setGroup(reds,6,LOW);
  setGroup(blues,6,LOW);
}

// 9
void wigWagSplit() {
  for(int i=0;i<3;i++){
    digitalWrite(reds[i],HIGH);
    digitalWrite(blues[i+3],HIGH);
  }
  flickerBase();
  delay(100);
  setGroup(reds,6,LOW);
  setGroup(blues,6,LOW);
}

// 10
void quadFlash() {
  for(int i=0;i<2;i++){
    for(int j=0;j<6;j+=2){
      digitalWrite(reds[j],HIGH);
      digitalWrite(blues[j],HIGH);
    }
    flickerBase();
    delay(80);
    setGroup(reds,6,LOW);
    setGroup(blues,6,LOW);
    delay(60);
  }
}

// 11
void sideAttack() {
  for(int i=0;i<6;i++){
    digitalWrite(reds[i],HIGH);
    flickerBase();
    delay(30);
  }
  for(int i=0;i<6;i++){
    digitalWrite(blues[i],HIGH);
    flickerBase();
    delay(30);
  }
  setGroup(reds,6,LOW);
  setGroup(blues,6,LOW);
}

// 12
void machineGun() {
  for(int i=0;i<10;i++){
    setGroup(reds,6,HIGH);
    flickerBase();
    delay(35);
    setGroup(reds,6,LOW);
    setGroup(blues,6,HIGH);
    flickerBase();
    delay(35);
    setGroup(blues,6,LOW);
  }
}

// ================= HELPER =================
void setGroup(int arr[], int sz, bool state) {
  for(int i=0;i<sz;i++)
    digitalWrite(arr[i], state);
}
