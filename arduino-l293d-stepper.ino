/*
 * Nema 17 Stepper Motor Control with L293D
 *
 * This code controls your bipolar stepper motor using an L293D H-bridge IC.
 * The L293D has 2 H-bridges, perfect for a bipolar stepper (2 coils).
 *
 * Connections:
 * L293D Pin 1 (Enable 1,2) -> Arduino Pin 8 (or tie to +5V for always-on)
 * L293D Pin 2 (Input 1)    -> Arduino Pin 9
 * L293D Pin 7 (Input 2)    -> Arduino Pin 10
 * L293D Pin 9 (Enable 3,4) -> Arduino Pin 11 (or tie to +5V for always-on)
 * L293D Pin 10 (Input 3)   -> Arduino Pin 12
 * L293D Pin 15 (Input 4)   -> Arduino Pin 13
 *
 * L293D Pin 3 & 6  -> Coil A (motor wires 1 & 2)
 * L293D Pin 11 & 14 -> Coil B (motor wires 3 & 4)
 *
 * L293D Pin 4, 5, 12, 13 -> GND
 * L293D Pin 16 -> +5V (logic power)
 * L293D Pin 8  -> +12V (motor power)
 *
 * Motor: Nema 17 Bipolar, 1.8° step angle (200 steps per revolution)
 */

// Pin definitions
const int ENABLE_A = 8;   // Enable coil A (optional if tied to +5V)
const int COIL_A1 = 9;    // Coil A direction pin 1
const int COIL_A2 = 10;   // Coil A direction pin 2

const int ENABLE_B = 11;  // Enable coil B (optional if tied to +5V)
const int COIL_B1 = 12;   // Coil B direction pin 1
const int COIL_B2 = 13;   // Coil B direction pin 2

// Motor specifications
const int STEPS_PER_REV = 200;  // 1.8° per step = 360°/1.8° = 200 steps
const int STEP_DELAY = 5;       // Milliseconds between steps (adjust for speed)

// Step counter
int currentStep = 0;

void setup() {
  // Initialize all pins as outputs
  pinMode(ENABLE_A, OUTPUT);
  pinMode(COIL_A1, OUTPUT);
  pinMode(COIL_A2, OUTPUT);

  pinMode(ENABLE_B, OUTPUT);
  pinMode(COIL_B1, OUTPUT);
  pinMode(COIL_B2, OUTPUT);

  // Enable both coils
  digitalWrite(ENABLE_A, HIGH);
  digitalWrite(ENABLE_B, HIGH);

  // Initialize serial for debugging
  Serial.begin(9600);
  Serial.println("Stepper Motor Test - L293D Driver");
  Serial.println("Starting in 2 seconds...");
  delay(2000);
}

void loop() {
  // Example 1: Rotate one full revolution clockwise
  Serial.println("Rotating 1 revolution clockwise...");
  rotate(STEPS_PER_REV, true);
  delay(1000);

  // Example 2: Rotate one full revolution counter-clockwise
  Serial.println("Rotating 1 revolution counter-clockwise...");
  rotate(STEPS_PER_REV, false);
  delay(1000);

  // Example 3: Rotate 90 degrees (50 steps) clockwise
  Serial.println("Rotating 90 degrees clockwise...");
  rotate(STEPS_PER_REV / 4, true);
  delay(1000);

  // Example 4: Continuous slow rotation
  Serial.println("Continuous rotation for 5 seconds...");
  unsigned long startTime = millis();
  while (millis() - startTime < 5000) {
    stepMotor(true);
    delay(STEP_DELAY);
  }
  delay(1000);

  // Turn off coils to prevent heating when idle
  disableMotor();
  Serial.println("Motor disabled. Waiting 5 seconds...");
  delay(5000);
}

// Rotate a specific number of steps
void rotate(int steps, bool clockwise) {
  for (int i = 0; i < steps; i++) {
    stepMotor(clockwise);
    delay(STEP_DELAY);
  }
}

// Execute one step
void stepMotor(bool clockwise) {
  if (clockwise) {
    currentStep++;
    if (currentStep >= 4) currentStep = 0;
  } else {
    currentStep--;
    if (currentStep < 0) currentStep = 3;
  }

  setStep(currentStep);
}

// Set coil states for full-step mode
void setStep(int step) {
  switch (step) {
    case 0:  // Step 1
      digitalWrite(COIL_A1, HIGH);
      digitalWrite(COIL_A2, LOW);
      digitalWrite(COIL_B1, HIGH);
      digitalWrite(COIL_B2, LOW);
      break;

    case 1:  // Step 2
      digitalWrite(COIL_A1, LOW);
      digitalWrite(COIL_A2, HIGH);
      digitalWrite(COIL_B1, HIGH);
      digitalWrite(COIL_B2, LOW);
      break;

    case 2:  // Step 3
      digitalWrite(COIL_A1, LOW);
      digitalWrite(COIL_A2, HIGH);
      digitalWrite(COIL_B1, LOW);
      digitalWrite(COIL_B2, HIGH);
      break;

    case 3:  // Step 4
      digitalWrite(COIL_A1, HIGH);
      digitalWrite(COIL_A2, LOW);
      digitalWrite(COIL_B1, LOW);
      digitalWrite(COIL_B2, HIGH);
      break;
  }
}

// Disable motor (to prevent heating when idle)
void disableMotor() {
  digitalWrite(ENABLE_A, LOW);
  digitalWrite(ENABLE_B, LOW);

  // Also set all coil pins low
  digitalWrite(COIL_A1, LOW);
  digitalWrite(COIL_A2, LOW);
  digitalWrite(COIL_B1, LOW);
  digitalWrite(COIL_B2, LOW);
}

// Enable motor
void enableMotor() {
  digitalWrite(ENABLE_A, HIGH);
  digitalWrite(ENABLE_B, HIGH);
}

/*
 * HALF-STEP MODE (8 steps per cycle instead of 4)
 *
 * Uncomment this function and replace setStep() above to use half-stepping.
 * Half-stepping gives smoother motion and double the resolution (400 steps/rev).
 * Update STEPS_PER_REV to 400 at the top if using this.
 */
/*
void setStepHalf(int step) {
  switch (step % 8) {
    case 0:
      digitalWrite(COIL_A1, HIGH);
      digitalWrite(COIL_A2, LOW);
      digitalWrite(COIL_B1, LOW);
      digitalWrite(COIL_B2, LOW);
      break;
    case 1:
      digitalWrite(COIL_A1, HIGH);
      digitalWrite(COIL_A2, LOW);
      digitalWrite(COIL_B1, HIGH);
      digitalWrite(COIL_B2, LOW);
      break;
    case 2:
      digitalWrite(COIL_A1, LOW);
      digitalWrite(COIL_A2, LOW);
      digitalWrite(COIL_B1, HIGH);
      digitalWrite(COIL_B2, LOW);
      break;
    case 3:
      digitalWrite(COIL_A1, LOW);
      digitalWrite(COIL_A2, HIGH);
      digitalWrite(COIL_B1, HIGH);
      digitalWrite(COIL_B2, LOW);
      break;
    case 4:
      digitalWrite(COIL_A1, LOW);
      digitalWrite(COIL_A2, HIGH);
      digitalWrite(COIL_B1, LOW);
      digitalWrite(COIL_B2, LOW);
      break;
    case 5:
      digitalWrite(COIL_A1, LOW);
      digitalWrite(COIL_A2, HIGH);
      digitalWrite(COIL_B1, LOW);
      digitalWrite(COIL_B2, HIGH);
      break;
    case 6:
      digitalWrite(COIL_A1, LOW);
      digitalWrite(COIL_A2, LOW);
      digitalWrite(COIL_B1, LOW);
      digitalWrite(COIL_B2, HIGH);
      break;
    case 7:
      digitalWrite(COIL_A1, HIGH);
      digitalWrite(COIL_A2, LOW);
      digitalWrite(COIL_B1, LOW);
      digitalWrite(COIL_B2, HIGH);
      break;
  }
}
*/
