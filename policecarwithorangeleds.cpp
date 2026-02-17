// ================= PIN MAP =================
// Front / Rear
#define FW_L 2
#define FW_R 3
#define BR_L 4
#define BR_R 5

// Indicators
int indL[] = {6, 8};   // Left orange (front, back)
int indR[] = {7, 9};   // Right orange (front, back)

// Police lights
int redTop[]  = {10, 11, 12, 13};   // RED = LEFT
int blueTop[] = {A1, A2, A3, A4};   // BLUE = RIGHT

// Button
#define BTN A0
// ==========================================

int mode = 0;
int lastBtnState = HIGH;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 180;

// ---------- SETUP ----------
void setup() {
  pinMode(BTN, INPUT_PULLUP);

  int pins[] = {
    FW_L, FW_R, BR_L, BR_R,
    6,7,8,9,
    10,11,12,13,
    A1,A2,A3,A4
  };

  for (int i = 0; i < 16; i++) pinMode(pins[i], OUTPUT);
  allOff();
}

// ---------- LOOP ----------
void loop() {
  handleButton();

  switch (mode) {
    case 0: allOff(); break;
    case 1: headTailOn(); break;
    case 2: sideSingleAlt(); break;
    case 3: sideDoubleAlt(); break;
    case 4: sideTripleAlt(); break;
    case 5: sweepAlt(); break;
    case 6: sideChase(); break;
    case 7: indicatorDoubleRB(); break;
    case 8: comboSingleFlash(); break;

  }
}

// ---------- BUTTON HANDLER ----------
void handleButton() {
  int reading = digitalRead(BTN);

  if (reading == LOW && lastBtnState == HIGH) {
    if (millis() - lastDebounceTime > debounceDelay) {
      mode++;
      if (mode > 8) mode = 0;
      lastDebounceTime = millis();
    }
  }
  lastBtnState = reading;
}

// ---------- FUNCTIONS ----------

void allOff() {
  for (int p = 2; p <= 13; p++) digitalWrite(p, LOW);
  for (int p = A1; p <= A4; p++) digitalWrite(p, LOW);
}

void headTailOn() {
  allOff();
  digitalWrite(FW_L, HIGH);
  digitalWrite(FW_R, HIGH);
  digitalWrite(BR_L, HIGH);
  digitalWrite(BR_R, HIGH);
}

// CASE 2 – SIDE SINGLE ALTERNATING
void sideSingleAlt() {
  allOff();
  setGroup(redTop, 4, HIGH);
  digitalWrite(FW_L, HIGH);
  digitalWrite(BR_L, HIGH);
  setGroup(indL, 2, HIGH);
  delay(450);

  allOff();
  setGroup(blueTop, 4, HIGH);
  digitalWrite(FW_R, HIGH);
  digitalWrite(BR_R, HIGH);
  setGroup(indR, 2, HIGH);
  delay(450);
}

// CASE 3 – DOUBLE FLASH
void sideDoubleAlt() {
  for (int i = 0; i < 2; i++) {
    allOff();
    setGroup(redTop, 4, HIGH);
    digitalWrite(FW_L, HIGH);
    digitalWrite(BR_L, HIGH);
    setGroup(indL, 2, HIGH);
    delay(180);

    allOff();
    delay(150);
  }

  delay(200);

  for (int i = 0; i < 2; i++) {
    allOff();
    setGroup(blueTop, 4, HIGH);
    digitalWrite(FW_R, HIGH);
    digitalWrite(BR_R, HIGH);
    setGroup(indR, 2, HIGH);
    delay(180);

    allOff();
    delay(150);
  }

  delay(300);
}

// CASE 4 – TRIPLE FLASH
void sideTripleAlt() {
  for (int i = 0; i < 3; i++) {
    allOff();
    setGroup(redTop, 4, HIGH);
    digitalWrite(FW_L, HIGH);
    digitalWrite(BR_L, HIGH);
    setGroup(indL, 2, HIGH);
    delay(180);

    allOff();
    delay(150);
  }

  delay(200);

  for (int i = 0; i < 3; i++) {
    allOff();
    setGroup(blueTop, 4, HIGH);
    digitalWrite(FW_R, HIGH);
    digitalWrite(BR_R, HIGH);
    setGroup(indR, 2, HIGH);
    delay(180);

    allOff();
    delay(150);
  }

  delay(300);
}

// CASE 5 – TRUE SWEEP (LEFT ↔ RIGHT)
void sweepAlt() {

  // Step order: LEFT → RIGHT
  for (int i = 0; i < 4; i++) {

    // 🔴 LEFT SIDE STEP
    allOff();
    digitalWrite(redTop[i], HIGH);     // one red at a time
    setGroup(indL, 2, HIGH);            // left indicators
    digitalWrite(FW_L, HIGH);           // front left
    digitalWrite(BR_L, HIGH);           // back left
    delay(120);

    // 🔵 RIGHT SIDE STEP
    allOff();
    digitalWrite(blueTop[i], HIGH);     // one blue at a time
    setGroup(indR, 2, HIGH);             // right indicators
    digitalWrite(FW_R, HIGH);            // front right
    digitalWrite(BR_R, HIGH);            // back right
    delay(120);
  }
}

void sideChase() {
  // RED chase (LEFT side)
  for (int i = 0; i < 3; i++) {
    allOff();

    digitalWrite(redTop[i], HIGH);
    digitalWrite(redTop[i + 1], HIGH);

    digitalWrite(FW_L, HIGH);
    digitalWrite(BR_L, HIGH);
    setGroup(indL, 2, HIGH);

    delay(120);
  }

  delay(80);

  // BLUE chase (RIGHT side)
  for (int i = 0; i < 3; i++) {
    allOff();

    digitalWrite(blueTop[i], HIGH);
    digitalWrite(blueTop[i + 1], HIGH);

    digitalWrite(FW_R, HIGH);
    digitalWrite(BR_R, HIGH);
    setGroup(indR, 2, HIGH);

    delay(120);
  }

  delay(100);
}

void indicatorDoubleRB() {

  // 🔴 LEFT SIDE – double flash
  for (int i = 0; i < 2; i++) {
    allOff();

    // Indicators
    setGroup(indL, 2, HIGH);

    // Red (2 LEDs)
    digitalWrite(redTop[0], HIGH);
    digitalWrite(redTop[1], HIGH);

    // Front / Rear
    digitalWrite(FW_L, HIGH);
    digitalWrite(BR_L, HIGH);

    delay(180);

    allOff();
    delay(140);
  }

  delay(200); // side gap

  // 🔵 RIGHT SIDE – double flash
  for (int i = 0; i < 2; i++) {
    allOff();

    // Indicators
    setGroup(indR, 2, HIGH);

    // Blue (2 LEDs)
    digitalWrite(blueTop[2], HIGH);
    digitalWrite(blueTop[3], HIGH);

    // Front / Rear
    digitalWrite(FW_R, HIGH);
    digitalWrite(BR_R, HIGH);

    delay(180);

    allOff();
    delay(140);
  }

  delay(300); // cycle gap
}

void comboSingleFlash() {

  // 🔴🔵 STEP 1: Red + Blue single flash
  allOff();
  setGroup(redTop, 4, HIGH);
  setGroup(blueTop, 4, HIGH);
  delay(250);
  allOff();
  delay(200);

  // ⚪🔴 STEP 2: White ↔ Red single alternating

  // White
  digitalWrite(FW_L, HIGH);
  digitalWrite(FW_R, HIGH);
  delay(220);
  allOff();
  delay(150);

  // Red
  digitalWrite(BR_L, HIGH);
  digitalWrite(BR_R, HIGH);
  delay(220);
  allOff();
  delay(200);

  // 🔴🔵 STEP 3: Back to Red + Blue single flash
  setGroup(redTop, 4, HIGH);
  setGroup(blueTop, 4, HIGH);
  delay(250);
  allOff();
  delay(300);
}


// ---------- HELPER ----------
void setGroup(int arr[], int sz, bool s) {
  for (int i = 0; i < sz; i++) digitalWrite(arr[i], s);
}
