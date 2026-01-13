# Quick Start Guide - Your First Stepper Motor Project

## What You've Got

You have 10x Nema 17 stepper motors:
- **Type**: Bipolar (4 wires)
- **Current**: 1.0A per coil
- **Resistance**: 3.5Ω
- **Step Angle**: 1.8° (200 steps per full rotation)

## Recommended First Build: L293D Driver (Simplest)

This is the easiest way to get your motor spinning quickly!

### What to Order

**Minimum to get started (~$60):**
1. Arduino Uno or clone - $10-25
2. L293D ICs (5-pack) - $8
3. Breadboard + jumper wires - $10
4. 12V 2A power supply - $10
5. Barrel jack adapter - $8
6. Basic multimeter - $15

**What you already have:**
- ✅ Stepper motors
- ✅ Resistors (from your list)
- ✅ Capacitors (from your list)

### Wiring Diagram

```
L293D IC (16-pin DIP):
                  +-------+
  Enable A  -> 1 |       | 16 <- +5V (Arduino)
  Input A1  -> 2 |       | 15 <- Input B2
  Output A1 <- 3 |       | 14 -> Output B2
       GND  -> 4 | L293D | 13 <- GND
       GND  -> 5 |       | 12 <- GND
  Output A2 <- 6 |       | 11 -> Output B1
  Input A2  -> 7 |       | 10 <- Input B1
    +12V    -> 8 |       | 9  <- Enable B
                  +-------+

Arduino Connections:
- Pin 8  -> L293D Pin 1 (Enable A)
- Pin 9  -> L293D Pin 2 (Input A1)
- Pin 10 -> L293D Pin 7 (Input A2)
- Pin 11 -> L293D Pin 9 (Enable B)
- Pin 12 -> L293D Pin 10 (Input B1)
- Pin 13 -> L293D Pin 15 (Input B2)
- GND    -> L293D Pins 4,5,12,13 (all GNDs)
- 5V     -> L293D Pin 16

Motor Connections:
- Coil A Wire 1 -> L293D Pin 3
- Coil A Wire 2 -> L293D Pin 6
- Coil B Wire 1 -> L293D Pin 11
- Coil B Wire 2 -> L293D Pin 14

Power Supply:
- +12V -> L293D Pin 8
- GND  -> Common ground with Arduino
```

### Identifying Motor Wires

Your motor has 4 wires. Find the two coils:

1. Set multimeter to resistance (Ω) mode
2. Test resistance between each pair of wires
3. Wires with ~3.5Ω between them = one coil
4. Label them: Coil A (red/blue) and Coil B (green/black) - colors may vary

### Step-by-Step Assembly

1. **Insert L293D into breadboard**
   - Make sure chip straddles center gap
   - Pin 1 has a notch or dot marking

2. **Connect Arduino to L293D (6 wires)**
   - Arduino pins 8,9,10,11,12,13 to L293D as shown above

3. **Connect power**
   - Arduino 5V to L293D Pin 16
   - Arduino GND to L293D Pins 4,5,12,13
   - 12V supply positive to L293D Pin 8
   - 12V supply GND to common ground

4. **Connect motor**
   - Coil A to pins 3,6
   - Coil B to pins 11,14

5. **Add capacitor** (IMPORTANT!)
   - 100µF-1000µF electrolytic capacitor
   - Across 12V supply (positive to +12V, negative to GND)
   - This smooths power and prevents glitches

### Upload Code

1. Open `arduino-l293d-stepper.ino` in Arduino IDE
2. Select your board: Tools -> Board -> Arduino Uno
3. Select your port: Tools -> Port -> (your Arduino)
4. Click Upload
5. Open Serial Monitor (Tools -> Serial Monitor)
6. Set baud rate to 9600

### Troubleshooting

**Motor doesn't move:**
- Check all wire connections
- Verify motor coils with multimeter
- Check power supply is providing 12V
- Try swapping wires within a coil pair (reverses direction)

**Motor vibrates but doesn't turn:**
- Wrong coil identification - recheck with multimeter
- Try swapping coil A and coil B connections

**Motor gets hot:**
- Normal to be warm, but shouldn't be too hot to touch
- Add `disableMotor()` when not in use (already in example code)
- L293D has current limit of 600mA, so motor runs below full power

**Motor turns wrong direction:**
- Swap wires within one coil pair (e.g., swap pins 3 and 6)
- Or change code: make `clockwise` parameter opposite

## Better Build: A4988 Driver Module (Recommended for Projects)

Once you're comfortable, upgrade to A4988 modules:

### Why A4988 is Better
- **Only 2 Arduino pins needed** (vs 6 for L293D)
- **Microstepping** for smoother motion (up to 3200 steps/revolution!)
- **Full 1.0A support** (L293D limited to 600mA)
- **Easier wiring** - just STEP and DIR pins
- **Better for your photo projects**

### Wiring (Much Simpler!)

```
A4988 Module:
STEP -> Arduino Pin 3
DIR  -> Arduino Pin 2
ENABLE -> GND
MS1, MS2, MS3 -> GND (for full-step) or +5V for microstepping
VMOT -> +12V
GND  -> GND
VDD  -> +5V from Arduino

1B, 1A -> Coil A
2A, 2B -> Coil B
```

### Critical Step: Set Current Limit

**BEFORE powering motor:**
1. Measure voltage at potentiometer wiper (small screw on A4988)
2. Target: 0.64V for 0.8A (safe for your 1.0A motor)
3. Formula: Vref = Current × 8 × 0.1Ω = 0.8 × 0.8 = 0.64V
4. Adjust tiny potentiometer while measuring
5. Start low and increase gradually while testing

### Upload Code

Use `arduino-a4988-stepper.ino` - much simpler code!

## Next Steps for Your Photo Projects

### Photo Booth with Rollers
1. Use A4988 driver (you'll want smooth, precise motion)
2. Calculate steps per cm of paper advance
3. Use continuous rotation mode for chemistry development
4. Add limit switches to detect end of paper roll

### Pinhole Camera (1pm-2pm)
1. Add DS3231 Real-Time Clock module ($8 on Amazon)
2. Use shutter mechanism (stepper opens/closes cover)
3. See `arduino-advanced-examples.ino` for time-based code
4. Battery backup keeps time accurate

### Sun/Star Tracking
1. These need 2 motors (horizontal + vertical)
2. Order 2x A4988 modules
3. Build or buy gimbal mount
4. See advanced examples for tracking math

## Your Learning Path

**Week 1:** Get L293D circuit working, motor spinning
**Week 2:** Upgrade to A4988, experiment with microstepping
**Week 3:** Build simple shutter mechanism for camera
**Week 4:** Add RTC for timed exposures
**Ongoing:** Prototype your photo booth roller system!

## Common Beginner Mistakes to Avoid

1. ❌ **Forgetting the capacitor** on power supply → motor stutters
2. ❌ **Wrong current limit** on A4988 → motor overheats or stalls
3. ❌ **Not identifying coils correctly** → vibration, no rotation
4. ❌ **Trying to power from USB** → not enough current, Arduino resets
5. ❌ **Leaving motor enabled 24/7** → unnecessary heating and power waste
6. ❌ **No flyback diodes** (if building discrete circuit) → destroyed MOSFETs

## Safety Reminders

- ⚠️ Motor power should be **separate** from Arduino USB power
- ⚠️ Don't touch motor wires while powered - can get 12V shock (not dangerous but unpleasant)
- ⚠️ Stepper motors can get warm during operation - this is normal
- ⚠️ If anything smells like burning, **disconnect power immediately**

## Resources

All code and documentation in this folder:
- `stepper-driver-circuit.md` - Detailed circuit design
- `amazon-parts-list.md` - Complete shopping list
- `arduino-l293d-stepper.ino` - Beginner code (L293D)
- `arduino-a4988-stepper.ino` - Recommended code (A4988)
- `arduino-advanced-examples.ino` - Photo projects code

## Questions to Ask Yourself Before Ordering

1. **How much do I want to spend?**
   - Minimum: ~$60 (L293D route)
   - Recommended: ~$100 (includes A4988 modules for future projects)

2. **Do I have time to wait for shipping?**
   - Amazon Prime: 2 days
   - AliExpress: 4-6 weeks but 50% cheaper

3. **Do I have basic tools?**
   - Multimeter (essential!)
   - Wire strippers (helpful)
   - Soldering iron (needed for permanent builds later)

## Ready to Order?

Check `amazon-parts-list.md` and pick either:
- **Budget starter** (~$60) - L293D route, learn basics
- **Recommended starter** (~$100) - A4988 route, ready for projects

Good luck with your electronics journey! 🎉
