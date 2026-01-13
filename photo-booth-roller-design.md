# Photo Booth Roller System Design

## Problem: Will One Motor Drive 4 Rollers?

**Short answer: Probably not reliably with your 0.13 Nm motors.**

Your Nema 17 motors are on the lower end of the torque spectrum. For a reliable photo booth roller system handling wet paper through chemistry, you'll want either:
1. Multiple motors (one per roller section)
2. Stronger motors (0.4-0.6 Nm)
3. Gear reduction (2:1 or 3:1)

## Torque Math

### Your Motor Capability
- **Torque**: 0.13 Nm = 130 N·mm
- **At 30mm diameter roller** (15mm radius): F = 130/15 = **8.7N** (~880g force)
- **At 20mm diameter roller** (10mm radius): F = 130/10 = **13N** (~1.3kg force)

### What You're Fighting Against
1. **Static friction** of 4 roller bearings: ~2-4N
2. **Belt friction** and tension losses: ~10-20% per connection
3. **Wet paper drag** through chemistry: ~2-5N depending on bath viscosity
4. **Paper tension**: ~1-2N to keep paper flat

**Total estimated resistance**: 5-11N

**Verdict**: Marginal with small rollers, likely underpowered with larger rollers

## Recommended Designs

### Design A: Multi-Motor System (Best for Reliability)

```
Motor 1 → [Roller 1 & 2] ← Paper input
              ↓
Motor 2 → [Roller 3 & 4] ← Developer bath
              ↓
Motor 3 → [Roller 5 & 6] ← Fix bath
              ↓
Motor 4 → [Roller 7 & 8] ← Output/drying
```

**Advantages:**
- Each motor only drives 1-2 rollers
- Independent speed control at each stage
- Different chemistry baths can have different speeds
- Redundancy (one motor fails, others keep working)
- You have 10 motors, so use 3-4!

**Motor Control:**
```arduino
// Synchronized motor control
const int MOTOR_PINS[] = {2, 4, 6, 8};  // DIR pins
const int STEP_PINS[] = {3, 5, 7, 9};    // STEP pins
const int NUM_MOTORS = 4;

void advancePaper(int steps) {
  for (int i = 0; i < steps; i++) {
    for (int m = 0; m < NUM_MOTORS; m++) {
      digitalWrite(STEP_PINS[m], HIGH);
    }
    delayMicroseconds(1000);
    for (int m = 0; m < NUM_MOTORS; m++) {
      digitalWrite(STEP_PINS[m], LOW);
    }
    delayMicroseconds(1000);
  }
}

void setSpeed(int motorIndex, int speedDelay) {
  // Individual motor speed control for different bath times
}
```

### Design B: Single Motor with Gear Reduction

```
Motor → [2:1 Gearbox] → Timing belt → 4 Rollers
```

**Gear Ratio Options:**
- **2:1 reduction**: 0.26 Nm (2x torque, half speed)
- **3:1 reduction**: 0.39 Nm (3x torque, 1/3 speed)

**Advantages:**
- Simpler electronics (one driver)
- All rollers always synchronized
- Good for uniform chemistry processing

**Disadvantages:**
- Additional mechanical complexity
- Single point of failure
- Fixed speed for all stages

### Design C: Upgraded Motors

Replace with higher torque Nema 17:

| Motor Type | Torque | Price | Will Drive 4 Rollers? |
|------------|--------|-------|----------------------|
| Your current | 0.13 Nm | Have | ❌ Marginal |
| Standard | 0.4 Nm | $8 | ✅ Yes |
| High torque | 0.6 Nm | $12 | ✅ Easily |

**Amazon search terms:**
- "Nema 17 0.4Nm stepper motor"
- "Nema 17 high torque 42 stepper motor"

## Mechanical Components Needed

### For Belt-Driven Rollers

**GT2 Timing Belt System** (recommended):
- GT2 timing belt (2mm pitch)
- GT2 pulleys (20-tooth for motor shaft)
- GT2 pulleys for roller shafts
- Belt tensioner

**Why GT2:**
- Positive drive (no slipping)
- Designed for precision motion
- Common in 3D printers
- Cheap ($15 for belt + pulleys)

**Alternative - O-Ring Drive** (simpler):
- Rubber O-rings as belts
- 3D print or buy small pulleys
- Less precision but easier to build
- Good for prototyping

### Roller Construction

**Option 1: PVC Pipe Rollers**
- 3/4" or 1" PVC pipe
- Cut to width of your paper
- Insert 1/4" or 5mm rod through center
- Mount in skateboard bearings (608ZZ)
- Cheap and waterproof!

**Option 2: 3D Printed Rollers**
- Print in PETG (chemical resistant)
- Add grooves for grip
- Insert bearing mounts
- Coat with PlastiDip for grip

**Option 3: Commercial Photo Rollers**
- Repurpose old printer rollers
- Check eBay for "developer tank roller"
- Already chemistry-resistant

### Bearings

**608ZZ Skateboard Bearings** (~$10 for 10):
- 8mm ID, 22mm OD
- Sealed (important for chemistry!)
- Low friction
- Standard size, easy to mount

### Frame

- Aluminum extrusion (8020 or similar)
- 3D printed brackets
- Acrylic sheets for chemistry trays
- Ensure everything is chemistry-resistant!

## Prototype Testing Plan

### Phase 1: Bench Test (No Chemistry)
1. Build 2-roller system with one motor
2. Use dry paper
3. Measure current draw and motor temperature
4. If motor struggles → add second motor or gears

### Phase 2: Single Bath Test
1. Add chemistry tray under rollers
2. Test with wet paper
3. Monitor for slipping or stalling
4. Adjust belt tension and roller grip

### Phase 3: Full System
1. Add all rollers and baths
2. Test timing (e.g., 60s in developer, 30s in fixer)
3. Fine-tune speeds for each stage
4. Add limit switches for safety

## Roller Diameter Recommendations

**Smaller diameter = less torque needed**

| Diameter | Linear Speed @ 60 RPM | Torque Needed | Best For |
|----------|----------------------|---------------|----------|
| 20mm | 3.8 cm/s | Lower | ✅ Your motors |
| 30mm | 5.7 cm/s | Medium | Marginal |
| 40mm | 7.5 cm/s | Higher | ❌ Need stronger motor |

**Recommendation**: Start with 20-25mm diameter rollers

## Paper Speed Calculation

For photo processing, you want slow, steady motion:

```arduino
// Calculate steps needed to advance paper by distance
float rollerDiameter = 20.0;  // mm
float paperDistance = 100.0;   // mm to advance
int stepsPerRev = 200;         // Full-step mode

float rollerCircumference = PI * rollerDiameter;
float revolutions = paperDistance / rollerCircumference;
int steps = revolutions * stepsPerRev;

// Example: 100mm paper advance with 20mm roller
// = 100 / (3.14159 * 20) = 1.59 revolutions
// = 1.59 * 200 = 318 steps
```

**Typical processing speeds:**
- Developer: 2-5 cm/s (slow)
- Stop bath: 5-10 cm/s (medium)
- Fixer: 2-5 cm/s (slow)
- Wash: 5-10 cm/s (medium)

## Parts Shopping List for Roller System

### Mechanical
- [ ] GT2 timing belt (2-3 meters) - $8
- [ ] GT2 pulleys, 20-tooth, 5mm bore (4-6x) - $12
- [ ] 608ZZ bearings (10-pack) - $10
- [ ] 5mm steel rod or shaft (for rollers) - $8
- [ ] PVC pipe (3/4" or 1", 3 feet) - $5
- [ ] Aluminum extrusion frame - $30
- [ ] 3D printed brackets/mounts - DIY

### Electronics (Multi-Motor Design)
- [ ] 4x A4988 driver modules - $10 (you'll have this)
- [ ] 4x Nema 17 motors - $0 (you have these!)
- [ ] 12V 5A power supply - $15 (more current for multiple motors)
- [ ] Arduino Mega - $20 (more pins for 4 motors)

### Chemistry Handling
- [ ] Acrylic trays (laser cut or buy) - $20
- [ ] Chemical-resistant tubing - $10
- [ ] Drain valves - $15
- [ ] Lab safety gear (gloves, goggles) - $20

**Total estimate: $150-200 for full roller system**

## Alternative: Use Your Current Motors for Position Control

Instead of continuous rollers, use steppers for:

1. **Precise paper positioning** - Move paper from bath to bath
2. **Shutter control** - Open/close during exposure
3. **Aperture control** - F-stop adjustment
4. **Film advance** - Single-frame advance for multi-exposure

These need less torque and play to the precision strengths of your motors!

## My Final Recommendation

**Start simple:**
1. Use 2-3 of your current motors (multi-motor design)
2. Build with 20mm diameter PVC rollers
3. Use O-rings as belts for prototyping
4. Test with one chemistry bath first

**Once proven:**
1. Upgrade to GT2 belts for production reliability
2. Consider upgrading to 0.4 Nm motors if needed
3. Add proper frame and chemistry trays
4. Integrate timing and safety controls

You have 10 motors to experiment with - take advantage of that! Better to use 3-4 motors than struggle with one underpowered motor.
