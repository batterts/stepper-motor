/*
 * Advanced Stepper Motor Examples for Photography Projects
 *
 * This file contains example code for your specific applications:
 * 1. Motorized shutter (timed exposure)
 * 2. Pinhole camera with time-based opening (1pm-2pm)
 * 3. Sun-tracking camera
 * 4. Star-tracking gimbal
 *
 * These examples assume you're using an A4988 driver module.
 * Adapt pin numbers and functions as needed for your setup.
 */

#include <Stepper.h>  // Optional: Arduino built-in stepper library

// ============================================================================
// EXAMPLE 1: Motorized Shutter with Timed Exposure
// ============================================================================

const int STEP_PIN = 3;
const int DIR_PIN = 2;
const int SHUTTER_OPEN_STEPS = 50;  // Adjust for your shutter mechanism

void shutterExample() {
  // Open shutter
  Serial.println("Opening shutter...");
  setDirection(true);
  rotate(SHUTTER_OPEN_STEPS);

  // Exposure time (e.g., 1 second)
  delay(1000);

  // Close shutter
  Serial.println("Closing shutter...");
  setDirection(false);
  rotate(SHUTTER_OPEN_STEPS);
}

// Shutter with variable exposure time
void timedExposure(int exposureMs) {
  openShutter();
  delay(exposureMs);
  closeShutter();
}

void openShutter() {
  setDirection(true);
  rotate(SHUTTER_OPEN_STEPS);
}

void closeShutter() {
  setDirection(false);
  rotate(SHUTTER_OPEN_STEPS);
}

// ============================================================================
// EXAMPLE 2: Pinhole Camera Open Between 1pm-2pm
// ============================================================================

// You'll need a Real-Time Clock module (DS3231) for accurate timekeeping
// Install library: RTClib by Adafruit
// #include <RTClib.h>
// RTC_DS3231 rtc;

void pinholeCameraScheduled() {
  /*
  // Initialize RTC
  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // Main loop
  while (true) {
    DateTime now = rtc.now();
    int currentHour = now.hour();

    // Open between 1pm (13:00) and 2pm (14:00)
    if (currentHour == 13) {
      if (!shutterOpen) {
        Serial.println("1pm - Opening shutter");
        openShutter();
        shutterOpen = true;
      }
    } else if (currentHour >= 14 && shutterOpen) {
      Serial.println("2pm - Closing shutter");
      closeShutter();
      shutterOpen = false;
    }

    delay(60000);  // Check every minute
  }
  */

  Serial.println("Example: Add RTC module and uncomment code above");
}

// ============================================================================
// EXAMPLE 3: Sun-Tracking System
// ============================================================================

// For accurate sun tracking, you need:
// - GPS module (for location) OR manual lat/long entry
// - RTC module (for accurate time)
// - Sun position calculation algorithm

// Simplified version using time-based approximation
void sunTrackingSimple() {
  /*
  // Very rough approximation (Northern Hemisphere)
  // Real implementation needs solar position algorithms

  DateTime now = rtc.now();
  int currentHour = now.hour();
  int currentMinute = now.minute();

  // Calculate hours since sunrise (assume 6am sunrise)
  float hoursSinceSunrise = (currentHour - 6) + (currentMinute / 60.0);

  // Sun moves ~15 degrees per hour (360° / 24 hours)
  float sunAzimuth = 90 + (hoursSinceSunrise * 15);  // Simplified!

  // Calculate steps needed to point at sun
  float currentAngle = getCurrentAngle();  // You'd track this
  float angleToMove = sunAzimuth - currentAngle;

  // Rotate to face sun
  rotateDegrees(angleToMove, angleToMove > 0);

  delay(60000);  // Update every minute
  */

  Serial.println("Sun tracking requires GPS + RTC + solar position math");
  Serial.println("See library: SolarCalculator or sunrise-equation");
}

// More advanced sun tracking with two-axis gimbal
void sunTrackingTwoAxis() {
  // You need 2 stepper motors:
  // - Azimuth motor (horizontal rotation, 0-360°)
  // - Altitude motor (vertical tilt, 0-90°)

  // Pseudo-code:
  // 1. Calculate sun position (azimuth, altitude) using solar equations
  // 2. Move azimuth motor to correct horizontal angle
  // 3. Move altitude motor to correct vertical angle
  // 4. Repeat every few minutes
}

// ============================================================================
// EXAMPLE 4: Star Tracking (Equatorial Mount)
// ============================================================================

// Stars move at rate of Earth's rotation: 360° per 23h 56m = ~15.04°/hour
const float SIDEREAL_RATE = 15.04;  // Degrees per hour
const float STEPS_PER_DEGREE = 200.0 / 360.0;  // For 200-step motor

void starTracking() {
  // Calculate steps per hour for sidereal tracking
  float stepsPerHour = SIDEREAL_RATE * STEPS_PER_DEGREE * 200;  // For full-step

  // Calculate delay between steps (in microseconds)
  unsigned long delayBetweenSteps = (3600UL * 1000000UL) / stepsPerHour;

  Serial.println("Star tracking mode - following Earth's rotation");
  Serial.print("Steps per hour: ");
  Serial.println(stepsPerHour);
  Serial.print("Delay between steps (us): ");
  Serial.println(delayBetweenSteps);

  // Continuous tracking loop
  setDirection(true);  // Westward motion (opposite of Earth's rotation)

  while (true) {
    step();
    delayMicroseconds(delayBetweenSteps);

    // In a real implementation, you'd:
    // - Check for user commands (stop, adjust rate, etc.)
    // - Monitor limit switches
    // - Implement periodic error correction
  }
}

// Star tracking with microstepping (smoother, more accurate)
void starTrackingMicrostepping() {
  // With 1/16 microstepping: 3200 steps per revolution
  // Much smoother tracking!

  const int MICROSTEPS_PER_REV = 3200;
  float stepsPerHour = SIDEREAL_RATE * (MICROSTEPS_PER_REV / 360.0);
  unsigned long delayBetweenSteps = (3600UL * 1000000UL) / stepsPerHour;

  // Set A4988 to 1/16 microstepping (MS1=MS2=MS3=HIGH)
  // Then run tracking loop

  Serial.println("Microstepping star tracking");
  Serial.print("Delay between microsteps (us): ");
  Serial.println(delayBetweenSteps);
}

// ============================================================================
// EXAMPLE 5: Bluetooth-Controlled Gimbal
// ============================================================================

// For Bluetooth control, add HC-05 or HC-06 module
// Connect: TX->RX, RX->TX, VCC->5V, GND->GND

void bluetoothGimbal() {
  /*
  // Read Bluetooth commands
  if (Serial.available() > 0) {
    char command = Serial.read();

    switch (command) {
      case 'U':  // Up
        rotateDegrees(5, true);
        break;
      case 'D':  // Down
        rotateDegrees(5, false);
        break;
      case 'L':  // Left (needs second motor)
        // Control azimuth motor
        break;
      case 'R':  // Right
        // Control azimuth motor
        break;
      case 'S':  // Stop
        disableMotor();
        break;
      case 'E':  // Enable
        enableMotor();
        break;
    }
  }
  */

  Serial.println("Add HC-05 Bluetooth module for wireless control");
}

// ============================================================================
// HELPER FUNCTIONS (referenced above)
// ============================================================================

int stepDelay = 1000;

void setDirection(bool clockwise) {
  digitalWrite(DIR_PIN, clockwise ? HIGH : LOW);
  delayMicroseconds(5);
}

void step() {
  digitalWrite(STEP_PIN, HIGH);
  delayMicroseconds(stepDelay);
  digitalWrite(STEP_PIN, LOW);
  delayMicroseconds(stepDelay);
}

void rotate(int steps) {
  for (int i = 0; i < steps; i++) {
    step();
  }
}

void rotateDegrees(float degrees, bool clockwise) {
  int stepsPerRev = 200;  // Adjust based on microstepping
  int steps = (int)((degrees / 360.0) * stepsPerRev);
  setDirection(clockwise);
  rotate(steps);
}

void disableMotor() {
  // Implementation depends on your setup
}

void enableMotor() {
  // Implementation depends on your setup
}

// ============================================================================
// MAIN SETUP AND LOOP
// ============================================================================

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("Advanced Stepper Examples");
  Serial.println("Uncomment the example you want to test in loop()");
}

void loop() {
  // Uncomment the example you want to test:

  // shutterExample();
  // timedExposure(2000);  // 2 second exposure
  // pinholeCameraScheduled();
  // sunTrackingSimple();
  // starTracking();
  // bluetoothGimbal();

  delay(1000);
}

/*
 * PARTS NEEDED FOR EACH PROJECT:
 *
 * 1. Motorized Shutter:
 *    - Stepper motor + A4988 driver
 *    - Small shutter mechanism (3D printed or modified camera shutter)
 *    - Optional: Limit switches for position sensing
 *
 * 2. Timed Pinhole Camera (1pm-2pm):
 *    - Stepper motor + A4988 driver
 *    - DS3231 Real-Time Clock module
 *    - Battery backup for RTC
 *    - Shutter mechanism
 *
 * 3. Sun Tracking:
 *    - 2x stepper motors (azimuth + altitude) + 2x A4988 drivers
 *    - DS3231 RTC module
 *    - Optional: GPS module (NEO-6M) for auto location
 *    - Optional: Light sensors for closed-loop tracking
 *    - Gimbal mount
 *
 * 4. Star Tracking:
 *    - Stepper motor + A4988 with microstepping
 *    - DS3231 RTC (accurate timing critical!)
 *    - Equatorial mount (can DIY or buy)
 *    - Counterweight for balance
 *    - Fine adjustment for polar alignment
 *
 * 5. Bluetooth Gimbal:
 *    - 2x stepper motors + 2x A4988 drivers
 *    - HC-05 or HC-06 Bluetooth module
 *    - 9V or 12V battery pack for portable operation
 *    - Gimbal frame (DIY or commercial)
 *    - Phone app for control
 */
