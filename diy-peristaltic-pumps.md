# DIY Peristaltic Pumps with Your Stepper Motors

## Why Use Your Motors for Pumps?

You have 10x Nema 17 stepper motors. Using 3 of them for peristaltic pumps is **perfect** for your photo processor:

### Advantages Over Commercial Pumps

| Feature | Commercial DC Pump | DIY Stepper Pump |
|---------|-------------------|------------------|
| Cost | $15 each = $45 | Essentially free |
| Flow control | Fixed or PWM | Precise stepping |
| Volume accuracy | ±10% | ±1% |
| Speed range | Limited | 0.1 to 100+ RPM |
| Reversible | Sometimes | Always |
| Chemistry compatibility | Varies | Depends on tubing only |
| Control | Relay on/off | Full Arduino integration |

### Perfect System Balance

**Motor allocation:**
- **1 motor**: Paper advance roller system
- **3 motors**: Peristaltic pumps (dev, stop, fix)
- **6 motors**: Future projects (shutters, tracking, etc.)

## How Peristaltic Pumps Work

```
Motor shaft rotates
     ↓
Rollers on arms compress tubing
     ↓
Creates moving compression wave
     ↓
Pushes fluid through tube

   ╔════Motor════╗
   ║      ↓      ║
   ║   [Roller]  ║ ← Compression roller
   ║      ║      ║
   ║   [Tube]════╬══> Fluid out
   ║      ║      ║
   ║   [Roller]  ║ ← Another roller (120° offset)
   ║             ║
   ╚═════════════╝
```

**Key principle**: Fluid only contacts tubing (not pump body), so chemistry never contaminates pump mechanism.

## 3D Printed Pump Design Options

### Option 1: Thingiverse "Customizable Peristaltic Pump"

**Search terms:**
- "peristaltic pump nema 17"
- "stepper motor peristaltic pump"
- "customizable peristaltic pump"

**Typical features:**
- Nema 17 mounting holes
- 3-6 compression rollers
- Adjustable tube channel
- 6mm tubing (standard)

**Print requirements:**
- Material: PETg or ABS (chemical resistant)
- Print time: 4-6 hours per pump
- Supports: Usually needed
- Infill: 30-50% (needs structural strength)

### Option 2: Parametric Design (OpenSCAD)

If you want to customize:
- Adjust roller count (more rollers = smoother flow)
- Change tube size
- Modify pump body for your frame

**Good if you know CAD, overkill if you just want to build**

### Option 3: Simple DIY Design

**Basic concept you can design yourself:**

```
Parts needed:
1. Motor mount plate
2. Rotor disk (attaches to motor shaft)
3. 3-4x Roller arms (attach to rotor)
4. Small bearings for rollers (608ZZ or 623)
5. Tube holder/channel (half-circle groove)
6. Tensioner (spring-loaded or bolt-adjustable)
```

## Parts Needed for 3 Pumps

### 3D Printed Parts
- [ ] 3x Pump bodies (4-6 hours each)
- [ ] 9-12x Roller arms
- [ ] 3x Tube holders
- [ ] 3x Tensioners

**Print settings:**
- Material: PETG (chemical resistant, strong)
  - Alternative: ABS (good) or PLA (okay for prototyping)
- Layer height: 0.2mm
- Infill: 30-50%
- Supports: Yes (usually)

### Hardware (Per Pump)

- [ ] 1x Nema 17 motor (you have these!)
- [ ] 3-4x Small bearings (608ZZ or 623) - $1 each
  - 608ZZ: 8mm ID, common skateboard bearing
  - 623: 3mm ID, smaller but adequate
- [ ] M3 or M4 bolts (various lengths) - $5 assortment
- [ ] Silicone tubing (6mm ID, 1m per pump) - $3/meter
- [ ] Optional: 5mm to motor shaft coupler - $2

**Total hardware per pump: ~$10**
**Total for 3 pumps: ~$30** (vs $45 for commercial)

Plus you get better control!

### Electronics

You already need A4988 drivers for paper advance, just add 3 more:

- [ ] 3x A4988 stepper drivers - $6 (for pumps)
- [ ] Arduino Mega recommended - $20 (needs 12+ pins for 4 motors)
  - Or stick with Uno and use I2C expanders

## Flow Rate Calculations

### Understanding Flow Rate

**Flow rate depends on:**
1. Tube inner diameter (ID)
2. Motor RPM
3. Number of compression rollers
4. Rotor diameter

### Typical Values for 6mm ID Tubing

**Tube cross-section area:**
- 6mm ID = 3mm radius
- Area = π × r² = 3.14159 × 3² = 28.3 mm²

**Volume per revolution:**
Depends on pump rotor diameter (typically 40-60mm)
- Approximate: 0.5 - 2 ml per revolution
- Let's assume 1 ml/rev for planning

**Flow rate formula:**
```
Flow (ml/min) = Volume_per_rev × RPM

Examples at 1 ml/rev:
- 10 RPM = 10 ml/min (slow, precise)
- 50 RPM = 50 ml/min (good for developer)
- 100 RPM = 100 ml/min (fast, stop bath)
- 200 RPM = 200 ml/min (very fast)
```

### Calibration Process

1. **Fill tubing with water**
2. **Run pump for exactly 100 steps** (at known microstepping)
3. **Measure output volume** with graduated cylinder
4. **Calculate ml per step**
5. **Store in Arduino code as calibration constant**

```arduino
// Calibration constants (measure these!)
const float ML_PER_REV_DEV = 1.2;   // Developer pump
const float ML_PER_REV_STOP = 1.15;  // Stop bath pump
const float ML_PER_REV_FIX = 1.18;   // Fixer pump

// Function to pump specific volume
void pumpVolume(int pumpMotor, float ml) {
  float mlPerRev = ML_PER_REV_DEV; // Select based on pump
  int revolutions = ml / mlPerRev;
  int steps = revolutions * 200;  // 200 steps per rev

  for (int i = 0; i < steps; i++) {
    stepPump(pumpMotor);
    delayMicroseconds(5000);  // Adjust for desired flow rate
  }
}
```

## Arduino Control for Multiple Steppers

### Pin Assignment (Arduino Mega Recommended)

```arduino
// Paper advance motor
const int PAPER_STEP = 2;
const int PAPER_DIR = 3;

// Pump motors
const int PUMP_DEV_STEP = 4;
const int PUMP_DEV_DIR = 5;

const int PUMP_STOP_STEP = 6;
const int PUMP_STOP_DIR = 7;

const int PUMP_FIX_STEP = 8;
const int PUMP_FIX_DIR = 9;

// Enable pins (can share one for all motors)
const int ENABLE_ALL = 10;
```

### Coordinated Control Code

```arduino
/*
 * Photo Processor with DIY Peristaltic Pumps
 * Controls paper advance + 3 stepper-driven pumps
 */

// Motor pin definitions
struct Motor {
  int stepPin;
  int dirPin;
  int stepsPerML;  // Calibration value
};

Motor paperMotor = {2, 3, 0};  // Steps per ML not applicable
Motor devPump = {4, 5, 167};    // Example: 167 steps = 1ml
Motor stopPump = {6, 7, 174};
Motor fixPump = {8, 9, 171};

const int ENABLE_PIN = 10;

void setup() {
  // Initialize all pins
  pinMode(paperMotor.stepPin, OUTPUT);
  pinMode(paperMotor.dirPin, OUTPUT);
  pinMode(devPump.stepPin, OUTPUT);
  pinMode(devPump.dirPin, OUTPUT);
  pinMode(stopPump.stepPin, OUTPUT);
  pinMode(stopPump.dirPin, OUTPUT);
  pinMode(fixPump.stepPin, OUTPUT);
  pinMode(fixPump.dirPin, OUTPUT);
  pinMode(ENABLE_PIN, OUTPUT);

  digitalWrite(ENABLE_PIN, LOW);  // Enable all motors

  Serial.begin(9600);
  Serial.println("Photo Processor with Peristaltic Pumps Ready");
}

void loop() {
  // Full processing cycle
  processSheet();
  delay(5000);  // Wait for next sheet
}

void processSheet() {
  Serial.println("Starting development...");

  // Developer stage: advance paper slowly while pumping developer
  unsigned long devStartTime = millis();
  int devFlowRate = 60;  // ml/min

  while (millis() - devStartTime < 60000) {  // 60 seconds
    // Advance paper one step
    stepMotor(paperMotor, 1000);  // Slow

    // Pump developer
    pumpAtRate(devPump, devFlowRate);

    delay(10);
  }

  Serial.println("Stop bath...");

  // Quick advance to stop bath zone
  advancePaper(500, 2000);  // 500 steps, fast

  // Stop bath stage
  unsigned long stopStartTime = millis();
  int stopFlowRate = 100;  // ml/min (faster)

  while (millis() - stopStartTime < 30000) {  // 30 seconds
    stepMotor(paperMotor, 800);  // Medium speed
    pumpAtRate(stopPump, stopFlowRate);
    delay(10);
  }

  Serial.println("Fixer...");

  // Advance to fixer
  advancePaper(500, 2000);

  // Fixer stage
  unsigned long fixStartTime = millis();
  int fixFlowRate = 60;  // ml/min

  while (millis() - fixStartTime < 60000) {  // 60 seconds
    stepMotor(paperMotor, 1000);
    pumpAtRate(fixPump, fixFlowRate);
    delay(10);
  }

  // All done, advance to output
  Serial.println("Advancing to output...");
  advancePaper(1000, 500);  // Fast advance

  Serial.println("Sheet complete!");
}

// Step a motor with delay
void stepMotor(Motor &motor, int delayMicros) {
  digitalWrite(motor.stepPin, HIGH);
  delayMicroseconds(delayMicros);
  digitalWrite(motor.stepPin, LOW);
  delayMicroseconds(delayMicros);
}

// Advance paper specific number of steps
void advancePaper(int steps, int delayMicros) {
  for (int i = 0; i < steps; i++) {
    stepMotor(paperMotor, delayMicros);
  }
}

// Pump at specific flow rate (ml/min)
void pumpAtRate(Motor &pump, int mlPerMin) {
  // Calculate steps needed for one loop iteration (10ms)
  float mlPerMs = mlPerMin / 60000.0;
  float mlPer10Ms = mlPerMs * 10;
  int steps = mlPer10Ms * pump.stepsPerML;

  for (int i = 0; i < steps; i++) {
    digitalWrite(pump.stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(pump.stepPin, LOW);
    delayMicroseconds(500);
  }
}

// Pump exact volume
void pumpVolume(Motor &pump, float ml) {
  int steps = ml * pump.stepsPerML;

  digitalWrite(pump.dirPin, HIGH);  // Forward

  for (int i = 0; i < steps; i++) {
    digitalWrite(pump.stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(pump.stepPin, LOW);
    delayMicroseconds(1000);
  }
}

// Purge pump (reverse to clear tubing)
void purgePump(Motor &pump, float ml) {
  int steps = ml * pump.stepsPerML;

  digitalWrite(pump.dirPin, LOW);  // Reverse

  for (int i = 0; i < steps; i++) {
    digitalWrite(pump.stepPin, HIGH);
    delayMicroseconds(500);
    digitalWrite(pump.stepPin, LOW);
    delayMicroseconds(500);
  }
}
```

## Advanced: Non-Blocking Multi-Motor Control

For smooth simultaneous operation of paper + pumps:

```arduino
// Use AccelStepper library (install from Library Manager)
#include <AccelStepper.h>

AccelStepper paperMotor(AccelStepper::DRIVER, 2, 3);
AccelStepper devPump(AccelStepper::DRIVER, 4, 5);
AccelStepper stopPump(AccelStepper::DRIVER, 6, 7);
AccelStepper fixPump(AccelStepper::DRIVER, 8, 9);

void setup() {
  paperMotor.setMaxSpeed(1000);
  devPump.setMaxSpeed(500);
  stopPump.setMaxSpeed(500);
  fixPump.setMaxSpeed(500);
}

void loop() {
  // Set targets
  paperMotor.moveTo(5000);  // Advance 5000 steps
  devPump.moveTo(10000);    // Pump continuously

  // Run all motors simultaneously (non-blocking)
  while (paperMotor.distanceToGo() != 0 || devPump.distanceToGo() != 0) {
    paperMotor.run();
    devPump.run();
    stopPump.run();
    fixPump.run();
  }
}
```

This is much smoother and allows true parallel operation!

## Tips for Success

### 3D Printing

1. **Use PETG** - PLA works but degrades with chemistry exposure
2. **Print pump bodies solid** - Higher infill for strength
3. **Test fit bearings** - May need to adjust hole sizes
4. **Sand contact surfaces** - Smoother = better sealing

### Tubing Selection

**Recommended: Silicone tubing**
- Size: 6mm ID, 10mm OD (or 1/4" ID)
- Chemistry resistant
- Flexible enough to compress
- Food-grade is fine

**Where to buy:**
- Amazon: "6mm silicone tubing"
- Hardware stores: Aquarium section
- Medical supply: Lab-grade (expensive but best)

### Assembly

1. **Don't over-tighten tensioner** - Tube should compress but not flatten
2. **Check roller alignment** - All rollers should contact tube evenly
3. **Pre-fill tubing** - Easier to start with liquid already in tube
4. **Test with water** - Always test before using chemistry!

### Maintenance

- **Replace tubing periodically** - Every 50-100 hours or when worn
- **Check bearings** - Replace if rough or noisy
- **Clean rotor** - Chemistry can build up, wipe with water
- **Lubricate motor shaft coupling** - Light oil on shaft

## Troubleshooting

### Pump Not Flowing

1. **Tensioner too loose** - Increase compression on tube
2. **Tube too stiff** - Use softer silicone
3. **Air bubble** - Pre-fill tubing, run backwards to purge
4. **Motor direction wrong** - Reverse direction in code

### Inconsistent Flow

1. **Worn tubing** - Replace (tubes wear out)
2. **Roller misalignment** - Check all rollers contact tube
3. **Motor skipping steps** - Reduce speed or increase driver current
4. **Tube kinked** - Check inlet/outlet aren't bent

### Low Flow Rate

1. **Need faster motor speed** - Increase RPM
2. **Tube too small** - Consider 8mm ID tubing
3. **Not enough compression** - Adjust tensioner
4. **Restriction downstream** - Check spray bar isn't clogged

## Cost Comparison: DIY vs Commercial

### DIY Stepper Pumps (3 pumps)
- 3x motors: $0 (you have them!)
- Hardware (bearings, bolts): $30
- Tubing: $15
- 3x A4988 drivers: $6
- **Total: ~$51**

### Commercial Peristaltic Pumps
- 3x 12V DC pumps: $45
- 3x relay modules: $8
- Tubing: $15
- **Total: $68**

**Savings: $17**

But more importantly:
- ✅ **Much better control** (precise stepping vs on/off)
- ✅ **Volume accuracy** (±1% vs ±10%)
- ✅ **Variable speed** without PWM complexity
- ✅ **Reversible** for purging/maintenance
- ✅ **Integrated with paper motor** (synchronized control)

## Recommended Approach

### Phase 1: Prove Concept with Commercial Pump
- Buy 1x cheap aquarium pump ($10)
- Build paper advance with 1 motor
- Test the drizzle concept
- Make sure system works

### Phase 2: Build DIY Pumps
- Find pump design on Thingiverse
- Print one pump
- Test and calibrate
- If it works, print 2 more

### Phase 3: Full System
- Replace commercial pump with DIY pumps
- Add synchronized control
- Fine-tune flow rates
- Build enclosure

This way you don't commit to 3D printing pumps until you've proven the overall concept!

## Example Pump Designs to Search For

**On Thingiverse:**
1. "Peristaltic Pump for Nema 17"
2. "Stepper Motor Dosing Pump"
3. "Parametric Peristaltic Pump"
4. "Nema17 Peristaltic Pump v2"

**On Printables:**
1. "Compact Peristaltic Pump"
2. "Modular Peristaltic Pump System"

**On YouTube:**
- Search: "DIY peristaltic pump nema 17"
- Watch build videos to see assembly

## Next Steps

1. **Search for pump designs** - Spend 30 min browsing options
2. **Order tubing and bearings** - $20 total, needed regardless
3. **Print one test pump** - See if you like it
4. **Test with water** - Calibrate flow rate
5. **If successful, print 2 more** - Complete your system!

Using your motors for pumps is a great way to maximize your 10-pack and gives you professional-grade control at DIY prices!
