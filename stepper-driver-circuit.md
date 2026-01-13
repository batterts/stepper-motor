# Simple Stepper Motor Driver Circuit

## Overview
This circuit drives your Nema 17 bipolar stepper motor (1.0A, 3.5Ω) using discrete MOSFETs. It's designed to be controlled by an Arduino.

## Circuit Design

### What You're Building
A bipolar stepper motor has 2 coils (A and B). Each coil needs to be driven in BOTH directions to create the magnetic fields that make the motor turn. This requires 4 "switches" per coil - this is called an H-bridge.

### Components Needed Per Coil (x2 total)
- 4x N-Channel MOSFETs (e.g., IRLZ44N or similar logic-level)
  - Must handle at least 1.5A continuous current
  - Must be "logic-level" (turns on with 5V from Arduino)
- 4x Flyback diodes (e.g., 1N4007 or Schottky like 1N5819)
  - Protects MOSFETs from voltage spikes when coil turns off
- 4x Gate resistors (220Ω - 1kΩ)
  - Limits current into MOSFET gates
- 2x Pull-down resistors (10kΩ)
  - Keeps MOSFETs off when Arduino pins are floating

### Power Supply
- 6-12V DC power supply (2A minimum)
- The motor draws 1.0A per phase, so 2A total when both coils are energized

### Why MOSFETs Instead of BJTs?
- MOSFETs are voltage-controlled (easier to drive from Arduino)
- More efficient at 1.0A
- Less heat generation
- Logic-level MOSFETs work directly with 5V Arduino signals

## Simplified Circuit (One Phase/Coil)

```
                    +12V
                     |
                     |
         +-----------+-----------+
         |                       |
         |                       |
      [Q1 MOSFET]             [Q2 MOSFET]
         |                       |
         +-------[COIL A]--------+
         |                       |
      [Q3 MOSFET]             [Q4 MOSFET]
         |                       |
         +-----------+-----------+
                     |
                    GND

Each MOSFET has:
- Gate connected to Arduino via 220Ω resistor
- Flyback diode across Drain-Source
- 10kΩ pull-down on gates of Q1/Q2
```

## Control Pattern (Full Step)
You need 4 Arduino pins per coil, but there are better ways to control this (see L293D suggestion below).

### Step Sequence for Coil A:
| Step | Q1 | Q2 | Q3 | Q4 | Current Direction |
|------|----|----|----|----|-------------------|
| 1    | ON | OFF| OFF| ON | Forward           |
| 2    | OFF| ON | ON | OFF| Reverse           |
| 3    | OFF| OFF| OFF| OFF| Off               |
| 4    | ON | OFF| OFF| ON | Forward (repeat)  |

**WARNING**: Never turn on Q1+Q3 or Q2+Q4 simultaneously - this creates a short circuit!

## Beginner Recommendation

Building an H-bridge from scratch is educational but tricky. Consider these alternatives:

### Option 1: L293D IC (Recommended for First Build)
- Contains 2 H-bridges in one chip
- Built-in protection
- Drives up to 600mA per channel (your motor needs 1A, so it will run but at reduced torque)
- Cost: ~$2-3
- Only 4 Arduino pins needed (2 per coil)

### Option 2: Discrete MOSFET Build (Learning Project)
- Build exactly as described above
- More components to solder
- Better current handling
- Great for understanding how drivers work
- 8 Arduino pins needed (4 per coil) unless you add logic

### Option 3: A4988 Stepper Driver Module (Future Projects)
- Professional solution (~$5)
- Microstepping capability
- Only 2 Arduino pins (step + direction)
- Current limiting built-in
- Add to your Amazon order for future builds

## Wiring to Your Motor

Your Nema 17 has 4 wires. You need to identify the two coils:

1. Use a multimeter to measure resistance
2. Find pairs that have ~3.5Ω between them
3. Each pair is one coil
4. Label them: Coil A (A1, A2) and Coil B (B1, B2)

## Safety Notes

1. **Always** connect flyback diodes - without them, voltage spikes will destroy MOSFETs
2. **Never** connect both sides of an H-bridge ON simultaneously
3. Use a separate power supply for the motor (not USB power)
4. Add a large capacitor (100µF-1000µF) across your power supply to smooth current spikes
5. Test your circuit with a multimeter before connecting the motor

## Next Steps

1. Start with an L293D IC for your first build (easier, safer)
2. Once that works, try building the discrete MOSFET version
3. Graduate to A4988 modules for your photo booth projects (much better control)
