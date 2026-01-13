/*
 * Nema 17 Stepper Motor Control with A4988 Driver Module
 *
 * This code controls your bipolar stepper motor using an A4988 driver module.
 * The A4988 is MUCH easier to use than L293D or discrete components!
 *
 * Only 2 pins needed: STEP and DIRECTION
 *
 * A4988 Connections:
 * STEP -> Arduino Pin 3
 * DIR  -> Arduino Pin 2
 *
 * MS1, MS2, MS3 -> Connect for microstepping (see table below)
 * ENABLE -> GND (or Arduino pin if you want to disable motor)
 * RESET -> +5V (or leave floating)
 * SLEEP -> +5V (or tie to RESET)
 *
 * VMOT -> +12V (motor power supply)
 * GND (motor power) -> GND
 * VDD -> +5V (logic power from Arduino)
 * GND (logic) -> GND
 *
 * 1B, 1A -> Coil A of stepper (one pair of wires)
 * 2A, 2B -> Coil B of stepper (other pair of wires)
 *
 * Microstepping Selection (MS1, MS2, MS3):
 * MS1  MS2  MS3  | Resolution
 * LOW  LOW  LOW  | Full step (200 steps/rev)
 * HIGH LOW  LOW  | Half step (400 steps/rev)
 * LOW  HIGH LOW  | 1/4 step (800 steps/rev)
 * HIGH HIGH LOW  | 1/8 step (1600 steps/rev)
 * HIGH HIGH HIGH | 1/16 step (3200 steps/rev)
 *
 * IMPORTANT: Adjust current limit potentiometer on A4988 before first use!
 * Your motor is 1.0A, so set current to about 0.8A using the formula:
 * Current Limit = Vref / (8 × Rsense)
 * For A4988 with 0.1Ω sense resistors: Vref = 0.8A × 8 × 0.1 = 0.64V
 * Measure Vref between potentiometer and GND, adjust to ~0.64V
 */

// Pin definitions
const int STEP_PIN = 3;
const int DIR_PIN = 2;
const int ENABLE_PIN = 8;  // Optional - tie to GND if not used

// Motor specifications
// Adjust STEPS_PER_REV based on microstepping:
// Full step: 200
// Half step: 400
// 1/4 step: 800
// 1/8 step: 1600
// 1/16 step: 3200
const int STEPS_PER_REV = 200;  // Full step mode (MS1=MS2=MS3=LOW)

// Speed control (microseconds between steps)
int stepDelay = 1000;  // 1000µs = 1ms = moderate speed
                       // Lower = faster, but don't go below ~100µs

void setup() {
  // Initialize pins
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  // Enable the motor (LOW = enabled, HIGH = disabled)
  digitalWrite(ENABLE_PIN, LOW);

  // Initialize serial
  Serial.begin(9600);
  Serial.println("A4988 Stepper Motor Control");
  Serial.println("Steps per revolution: " + String(STEPS_PER_REV));
  Serial.println("Starting in 2 seconds...");
  delay(2000);
}

void loop() {
  // Example 1: One full revolution clockwise
  Serial.println("1 revolution clockwise");
  setDirection(true);
  rotate(STEPS_PER_REV);
  delay(1000);

  // Example 2: One full revolution counter-clockwise
  Serial.println("1 revolution counter-clockwise");
  setDirection(false);
  rotate(STEPS_PER_REV);
  delay(1000);

  // Example 3: 90 degree rotation
  Serial.println("90 degrees clockwise");
  setDirection(true);
  rotate(STEPS_PER_REV / 4);
  delay(1000);

  // Example 4: Variable speed demonstration
  Serial.println("Speed test: slow to fast");
  setDirection(true);
  for (int speed = 2000; speed >= 500; speed -= 100) {
    stepDelay = speed;
    rotate(10);  // 10 steps at each speed
  }
  delay(1000);

  // Example 5: Disable motor to prevent heating
  Serial.println("Disabling motor for 3 seconds...");
  disableMotor();
  delay(3000);
  enableMotor();

  // Reset speed
  stepDelay = 1000;
}

// Rotate a specific number of steps
void rotate(int steps) {
  for (int i = 0; i < steps; i++) {
    step();
  }
}

// Execute one step
void step() {
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(stepDelay);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(stepDelay);
}

// Set rotation direction
void setDirection(bool clockwise) {
  if (clockwise) {
    digitalWrite(DIR_PIN, HIGH);
  } else {
    digitalWrite(DIR_PIN, LOW);
  }
  delayMicroseconds(5);  // Give driver time to register direction change
}

// Disable motor (saves power, prevents heating)
void disableMotor() {
  digitalWrite(ENABLE_PIN, HIGH);
}

// Enable motor
void enableMotor() {
  digitalWrite(ENABLE_PIN, LOW);
  delay(1);  // Give driver time to wake up
}

// Set speed in RPM (revolutions per minute)
void setSpeedRPM(float rpm) {
  // Calculate microseconds per step
  // rpm × steps_per_rev / 60 seconds = steps per second
  // 1,000,000 µs / steps_per_second = µs per step
  float stepsPerSecond = (rpm * STEPS_PER_REV) / 60.0;
  stepDelay = (int)(500000.0 / stepsPerSecond);  // Divide by 2 for HIGH+LOW

  // Clamp to safe range
  if (stepDelay < 100) stepDelay = 100;  // Max speed limit
  if (stepDelay > 10000) stepDelay = 10000;  // Min speed limit
}

/*
 * ADVANCED FUNCTIONS FOR YOUR PHOTO BOOTH PROJECTS
 */

// Rotate to a specific angle (in degrees)
void rotateDegrees(float degrees, bool clockwise) {
  int steps = (int)((degrees / 360.0) * STEPS_PER_REV);
  setDirection(clockwise);
  rotate(steps);
}

// Accelerated rotation (smooth start/stop)
void rotateAccelerated(int steps, bool clockwise) {
  setDirection(clockwise);

  int accelSteps = min(steps / 4, 50);  // Accelerate over 1/4 distance or 50 steps
  int cruiseSteps = steps - (2 * accelSteps);

  // Acceleration phase
  for (int i = 0; i < accelSteps; i++) {
    int currentDelay = stepDelay * 2 - ((stepDelay * i) / accelSteps);
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(currentDelay);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(currentDelay);
  }

  // Cruise phase
  for (int i = 0; i < cruiseSteps; i++) {
    step();
  }

  // Deceleration phase
  for (int i = accelSteps; i > 0; i--) {
    int currentDelay = stepDelay * 2 - ((stepDelay * i) / accelSteps);
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(currentDelay);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(currentDelay);
  }
}

// Continuous rotation (for photo booth rollers)
// Call this repeatedly in loop() to keep motor running
void continuousRotation(bool clockwise, float rpm) {
  setDirection(clockwise);
  setSpeedRPM(rpm);
  step();
}

/*
 * PHOTO BOOTH APPLICATION EXAMPLE
 *
 * For your photo booth with chemistry rollers:
 * 1. Use continuous rotation while developing
 * 2. Use precise angle control for positioning
 * 3. Enable/disable to save power between uses
 * 4. Use acceleration for smooth starts/stops
 *
 * Example usage:
 *
 * // Advance photo paper 10cm through chemistry
 * setSpeedRPM(30);  // Slow, steady rotation
 * rotate(calculateStepsForDistance(10.0));  // You'd need to calculate this
 *
 * // Wait for development time
 * disableMotor();
 * delay(60000);  // 60 seconds
 *
 * // Advance to next bath
 * enableMotor();
 * rotate(calculateStepsForDistance(15.0));
 */
