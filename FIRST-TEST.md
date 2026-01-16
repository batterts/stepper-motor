# First Test - A4988 and Nema 17 Motor

## Congratulations on Getting Your A4988 Drivers!

Now let's get your first motor spinning safely and correctly.

## What You Need for First Test

### You Have (or should have):
- [x] A4988 stepper driver modules
- [x] Nema 17 stepper motor (from your 10-pack)
- [ ] Arduino Uno (or compatible)
- [ ] Breadboard
- [ ] Jumper wires
- [ ] 12V power supply (2A minimum)
- [ ] USB cable for Arduino
- [ ] Multimeter (CRITICAL for safety!)

### Optional but Helpful:
- [ ] Barrel jack adapter (to connect 12V to breadboard)
- [ ] Small heat sinks (may be included with A4988)
- [ ] Small screwdriver (for current adjustment pot)

## CRITICAL FIRST STEP: Set Current Limit

**⚠️ DO THIS BEFORE CONNECTING MOTOR OR YOU MAY DAMAGE IT!**

### Why This Matters

Your motor is rated for 1.0A. If the A4988 tries to push more current, the motor will:
- Overheat
- Lose steps
- Potentially damage the driver or motor

### How to Set Current Limit

**Target: 0.8A** (80% of motor's 1.0A rating - safe margin)

**Formula for A4988:**
```
Vref = Current × 8 × Rsense
Vref = 0.8A × 8 × 0.1Ω = 0.64V
```

**Target Vref: 0.64V**

### Step-by-Step Adjustment

1. **Insert A4988 into breadboard** (don't connect anything yet)

2. **Connect ONLY power**:
   - VDD → Arduino 5V
   - GND → Arduino GND
   - VMOT → +12V power supply
   - GND (motor power) → Power supply GND

3. **Set multimeter to DC voltage** (20V range)

4. **Measure Vref**:
   - Black probe → Any GND pin on A4988
   - Red probe → Metal of potentiometer screw
   - Read voltage on multimeter

5. **Adjust potentiometer**:
   - Use tiny screwdriver
   - Turn clockwise → increase voltage
   - Turn counter-clockwise → decrease voltage
   - **Target: 0.64V**

6. **Start LOW (0.4V) and test first**:
   - Better to be too low than too high
   - You can increase if motor is weak

```
        A4988 Module (top view)

     [Potentiometer] ← Measure here with red probe
            ↓
     ╔══════════════╗
     ║   A   4   9  ║
     ║   9   9   8  ║
     ║   8   8   8  ║
     ╚══════════════╝
           ↑
     GND ← Black probe here
```

## Wiring Diagram

### A4988 to Arduino

```
A4988 Pin       →  Arduino Pin
─────────────────────────────
STEP            →  Pin 3
DIR             →  Pin 2
MS1             →  GND (full-step mode)
MS2             →  GND (full-step mode)
MS3             →  GND (full-step mode)
ENABLE          →  GND (always enabled)
RESET           →  +5V (or leave floating)
SLEEP           →  +5V (or tie to RESET)
VDD             →  5V
GND (logic)     →  GND

VMOT            →  +12V (from power supply)
GND (motor)     →  GND (common with Arduino GND)
```

### A4988 to Motor

First, identify your motor coils with a multimeter:

1. **Measure resistance between all wire pairs**
2. **Find pairs with ~3.5Ω** = one coil
3. **Label them:**
   - Coil A: Wire 1 & Wire 2
   - Coil B: Wire 3 & Wire 4

```
A4988 Pin  →  Motor Wire
────────────────────────
1B         →  Coil A Wire 1
1A         →  Coil A Wire 2
2A         →  Coil B Wire 1
2B         →  Coil B Wire 2
```

**Note**: Wire colors vary by manufacturer. Use multimeter, not colors!

### Full Wiring Diagram

```
                    +12V Power Supply
                         |
                         |
                      +──┴──+
                      |VMOT |
                      |     |
    Arduino           |A4988|           Stepper Motor
   ┌──────┐          |     |          ┌─────────────┐
   │  5V  ├──────────┤VDD  |          │  Coil A     │
   │      │          |     ├─1B───────┤  (red/blue) │
   │ Pin2 ├──────────┤DIR  ├─1A───────┤             │
   │      │          |     |          │             │
   │ Pin3 ├──────────┤STEP ├─2A───────┤  Coil B     │
   │      │          |     ├─2B───────┤ (grn/black) │
   │      │          |RST  |          └─────────────┘
   │      │     ┌────┤SLP  |
   │      │     │    |     |
   │  GND ├─────┴────┤GND  ├─────────┬─ Power GND
   └──────┘          |     |         │
                     | EN  |         │
                ┌────┤MS1  |         │
                ├────┤MS2  |         │
                └────┤MS3  |         │
                     └─────┘         │
                         |           │
                         └───────────┘

Notes:
- ENABLE → GND (motor always on)
- MS1, MS2, MS3 → GND (full-step mode)
- RESET & SLEEP → 5V (or tie together)
- Common ground between Arduino and power supply
```

## Breadboard Layout

```
           A4988 Module
              (top)
        ┌──────────────┐
        │  Micro-USB   │  ← Some have this for easy power
        └──────────────┘
         |||||||||||||||   ← Pins


Breadboard Rows:
─────────────────────────────
Row 1:  [ ][ ][ ][ ENABLE ][ MS1 ][ MS2 ][ MS3 ]

Row 2:  [ RESET ][ SLEEP ][ STEP ][ DIR ]

Row 3:  [ Empty row for spacing ]

Row 4:  [ GND ][ GND ][ VDD ][ 1B ][ 1A ][ 2A ][ 2B ][ VMOT ]

Connection Guide:
- Pin 2 (Arduino) → STEP (Row 2)
- Pin 3 (Arduino) → DIR (Row 2)
- 5V (Arduino) → VDD (Row 4)
- 5V (Arduino) → RESET & SLEEP (Row 2)
- GND (Arduino) → GND (Row 4)
- GND (Arduino) → ENABLE, MS1, MS2, MS3 (Row 1)
- +12V (power) → VMOT (Row 4)
- GND (power) → GND (Row 4)
- Motor wires → 1B, 1A, 2A, 2B (Row 4)
```

## Upload and Test Code

### Option 1: Simple Test (No Library)

Use the code from `arduino-a4988-stepper.ino` in this repo.

1. Open Arduino IDE
2. Load `arduino-a4988-stepper.ino`
3. Select board: Tools → Board → Arduino Uno
4. Select port: Tools → Port → (your Arduino)
5. Click Upload
6. Open Serial Monitor (115200 baud)

### Option 2: Super Simple Test Code

If you just want to see it move ASAP:

```arduino
// Minimal A4988 Test
const int STEP_PIN = 3;
const int DIR_PIN = 2;

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);

  Serial.begin(9600);
  Serial.println("Motor Test Starting...");
  delay(2000);
}

void loop() {
  // One rotation clockwise
  digitalWrite(DIR_PIN, HIGH);
  for (int i = 0; i < 200; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(2000);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(2000);
  }

  delay(1000);

  // One rotation counter-clockwise
  digitalWrite(DIR_PIN, LOW);
  for (int i = 0; i < 200; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(2000);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(2000);
  }

  delay(1000);
}
```

## What Should Happen

### ✅ Success Looks Like:
- Motor shaft rotates smoothly
- One full rotation = 200 steps (1.8° per step)
- Motor is warm but not hot to touch
- No unusual sounds
- Direction reverses as expected

### ⚠️ Problems and Solutions

#### Motor Vibrates But Doesn't Turn
**Cause**: Wrong coil wiring
**Fix**:
- Swap wires within one coil (e.g., swap 1B and 1A)
- Or swap the two coils entirely

#### Motor Doesn't Move At All
**Causes**:
1. **Current limit too low** → Increase Vref gradually
2. **Wiring error** → Double-check all connections
3. **Motor wires** → Verify coils with multimeter
4. **Driver not enabled** → Check ENABLE is connected to GND

#### Motor Gets Very Hot
**Causes**:
1. **Current limit too high** → Decrease Vref to 0.6V or lower
2. **Motor left energized** → Normal to be warm when holding position
3. **Driver heat sink missing** → Add heat sink to A4988

#### Motor Skips Steps
**Causes**:
1. **Speed too fast** → Increase delay in code (try 3000 microseconds)
2. **Current too low** → Increase Vref slightly
3. **Power supply inadequate** → Check voltage under load

#### Driver Gets Hot
**Normal** - A4988 dissipates heat
**Fix**:
- Add heat sink (should be included with module)
- Use thermal adhesive or pads
- Ensure good airflow

#### Motor Turns Wrong Direction
**Not a problem!** Just swap direction in code or swap one coil's wires.

## Testing Checklist

- [ ] Set current limit to 0.64V (or start at 0.4V)
- [ ] Identify motor coils with multimeter
- [ ] Wire A4988 to Arduino (STEP, DIR, power)
- [ ] Wire motor to A4988 (1B, 1A, 2A, 2B)
- [ ] Connect 12V power supply
- [ ] Upload test code
- [ ] Open serial monitor
- [ ] Observe motor rotation
- [ ] Check motor temperature (should be warm, not hot)
- [ ] Test direction reversal
- [ ] Try different speeds (adjust delay)

## Next Steps After Success

Once your motor is spinning reliably:

### 1. Experiment with Speed
```arduino
// Very slow
delayMicroseconds(5000);  // Slow, precise

// Medium
delayMicroseconds(1000);  // Good general speed

// Fast
delayMicroseconds(500);   // Fast, may skip if too fast

// Very fast
delayMicroseconds(200);   // Pushing limits
```

### 2. Try Microstepping

Change MS1, MS2, MS3 connections:

```
MS1   MS2   MS3   Result
───   ───   ───   ──────
GND   GND   GND   Full step (200 steps/rev)
5V    GND   GND   Half step (400 steps/rev)
GND   5V    GND   1/4 step (800 steps/rev)
5V    5V    GND   1/8 step (1600 steps/rev)
5V    5V    5V    1/16 step (3200 steps/rev)
```

**Benefits of microstepping:**
- Smoother motion
- Less vibration
- Better for slow speeds
- More precise positioning

**Drawbacks:**
- Less torque per step
- More steps to move same distance

### 3. Build Your First Project

Now that you have a working motor:

**Simple projects:**
- [ ] Motorized turntable (product photography)
- [ ] Simple shutter mechanism
- [ ] Paper advance roller (test for photo booth)

**Next additions:**
- [ ] Add second motor
- [ ] Add push buttons for manual control
- [ ] Add LCD display for status
- [ ] Add limit switches for homing

### 4. Start Photo Booth Prototype

**Phase 1: Paper advance test**
1. Build 2-roller system with PVC pipe
2. Connect with O-ring or belt
3. Test advancing paper at different speeds
4. Calculate steps needed per cm of paper

**Phase 2: Add first pump**
1. Order or 3D print peristaltic pump
2. Add pump control (second motor or relay)
3. Test water drizzle over moving paper
4. Tune flow rate and paper speed

## Safety Reminders

⚠️ **Always set current limit FIRST!**
⚠️ **Don't connect/disconnect motor while powered**
⚠️ **Don't exceed 12V on VMOT** (A4988 max is ~35V but stick to 12V)
⚠️ **Add heat sink to A4988** (included in most kits)
⚠️ **Use adequate power supply** (2A minimum for one motor)
⚠️ **Common ground** between Arduino and motor power supply

## Troubleshooting Resources

1. **This repo's documentation**:
   - `arduino-a4988-stepper.ino` - Full code with examples
   - `QUICK-START.md` - General getting started guide
   - `stepper-driver-circuit.md` - Theory and details

2. **Serial Monitor is your friend**:
   - Shows what the code is doing
   - Use `Serial.println()` to debug

3. **Multimeter checks**:
   - Motor coils: Should be ~3.5Ω
   - Power supply: Should be ~12V
   - Vref: Should be 0.64V
   - Arduino 5V pin: Should be ~5V

## Common Questions

**Q: Can I power the Arduino from the 12V supply?**
A: Yes, through the barrel jack (7-12V input). But DON'T connect 12V to the 5V pin!

**Q: How many motors can one power supply run?**
A: Each motor draws ~1A. A 2A supply = 1 motor safely. For 3-4 motors, get a 5A supply.

**Q: Can I use a 9V battery?**
A: Yes for testing, but it won't last long. Use a wall supply for real projects.

**Q: My motor makes a high-pitched sound**
A: Normal at certain speeds. Try microstepping for quieter operation.

**Q: The motor holds position even when not moving**
A: Normal! Steppers have "holding torque". To disable, set ENABLE pin HIGH.

**Q: How do I make it go faster?**
A: Reduce the delay in the code, but there's a limit before steps are missed.

**Q: Direction is reversed from what I expect**
A: Swap wires of ONE coil, or change DIR pin logic in code.

## Success!

Once you have your motor spinning smoothly, you're ready to:
1. ✅ Add more motors for your photo booth
2. ✅ Start building mechanical systems (rollers, pumps)
3. ✅ Experiment with advanced control (acceleration, precise positioning)
4. ✅ Build your photography projects!

Post your success on the GitHub repo's issues/discussions!
