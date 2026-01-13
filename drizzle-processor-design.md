# Photo Chemistry Drizzle Processor Design

## Concept: Pump-Based Chemistry Application

Instead of pulling paper through chemistry baths, keep chemistry in closed containers and pump it over the paper. This is similar to commercial "spray bar" processors but DIY-friendly!

## Why This Design is Superior for DIY

### Advantages Over Roller Bath System
1. **Lower motor torque required** - Only advancing dry/damp paper
2. **Closed chemistry system** - Less oxidation, longer chemistry life
3. **Safety** - Reduced fumes and spills
4. **Smaller footprint** - No large trays needed
5. **Better chemistry economy** - Recirculate and reuse
6. **Temperature control** - Easier to maintain in closed containers
7. **Simpler mechanics** - Fewer moving parts in chemistry
8. **Your 0.13 Nm motors are perfect!** - No liquid resistance

### System Components

```
┌─────────────────────────────────────┐
│     Paper Path & Motor System      │
└─────────────────────────────────────┘
          ↓
    [Input Roller]
          ↓
    ╔═════════════╗
    ║ Developer   ║ ← Pump sprays from above
    ║ Zone        ║   Paper passes underneath
    ╚═════════════╝   Chemistry drains to tray
          ↓
    [Advance Roller]
          ↓
    ╔═════════════╗
    ║ Stop Bath   ║ ← Different pump
    ║ Zone        ║
    ╚═════════════╝
          ↓
    [Advance Roller]
          ↓
    ╔═════════════╗
    ║ Fixer Zone  ║ ← Different pump
    ╚═════════════╝
          ↓
    [Output Roller]
```

## Motor Requirements

### Simplified Torque Needs

**What you're moving:**
- Dry or damp paper: ~0.5-2N of resistance
- 2 rollers with bearings: ~1-2N friction
- Belt tension: ~1N

**Total: ~2-5N**

**Your motor capability at 20mm roller:**
- Can provide: 13N of force
- Needs: 2-5N
- **Safety margin: 2.6x to 6.5x** ✅ Perfect!

### Recommended Motor Setup

**Option A: Single Motor (Simplest)**
```
One stepper motor drives all rollers via belt
- Input roller: pulls paper from stack
- Middle rollers: maintain tension
- Output roller: driven by same belt

Motors needed: 1
Complexity: Low
Cost: ~$10 (one A4988)
```

**Option B: Two Motors (Better Control)**
```
Motor 1: Input + tension rollers
Motor 2: Output roller (can run slightly faster for drying tension)

Motors needed: 2
Complexity: Medium
Cost: ~$20 (two A4988)
```

**Option C: Multi-Stage with Individual Control**
```
Motor 1: Feed paper into developer
Motor 2: Developer to stop bath
Motor 3: Stop bath to fixer
Motor 4: Fixer to output

Motors needed: 4
Complexity: Higher
Cost: ~$40
Advantage: Can pause at any stage, variable speeds
```

**Recommendation: Start with Option A, expand to B if needed**

## Pump Selection

### Peristaltic Pumps (Recommended)

**Why Peristaltic:**
- ✅ Chemistry never touches pump internals (just tubing)
- ✅ No contamination between chemicals
- ✅ Self-priming
- ✅ Precise flow control
- ✅ Can run dry without damage
- ✅ Reversible for recirculation

**Types:**

1. **12V DC Peristaltic Pumps** ($15-30 each)
   - Simple on/off control via relay
   - Fixed flow rate (typically 60-100 ml/min)
   - Good for: continuous drizzle
   - Example: Kamoer KPP-ST peristaltic pump

2. **Stepper Motor Peristaltic Pumps** ($20-40)
   - Precise volume control
   - Variable speed
   - **Can use your spare Nema 17 motors!**
   - DIY pump head can be 3D printed
   - Good for: precise dosing

3. **Budget: Aquarium Pumps** ($10-15)
   - Not peristaltic, chemistry contacts impeller
   - Need separate pump for each chemistry
   - Less precise but cheap
   - Good for: prototyping

### Spray/Drizzle Heads

**Option 1: Spray Bar** (even distribution)
```
Chemistry flows through pipe with small holes
■■■■■■■■■■■■■■■■■
 ↓ ↓ ↓ ↓ ↓ ↓ ↓ ↓  (evenly spaced holes)
```
- PVC pipe with 1mm holes drilled every 10mm
- Even coverage across paper width
- DIY-friendly

**Option 2: Shower Head Style**
- Multiple drip points
- 3D printable
- Better agitation

**Option 3: Sheet Flow**
- Chemistry flows down a flat surface onto paper
- Very even coverage
- Use acrylic sheet at angle

### Flow Rates

**Developer:**
- 50-100 ml/min
- Goal: Keep paper surface wet but not pooling
- Paper advance speed: 2-5 cm/sec

**Stop Bath:**
- 100-150 ml/min (can be faster, just needs to rinse)
- Paper advance: 5-10 cm/sec

**Fixer:**
- 50-100 ml/min
- Paper advance: 2-5 cm/sec

## System Layout Options

### Layout A: Horizontal Processor

```
Side view:

    ┌─Developer─┐   ┌─Stop─┐   ┌─Fixer─┐
    │Container  │   │Bath  │   │       │
    └─────┬─────┘   └───┬──┘   └───┬───┘
          ↓             ↓          ↓
    Pump  Pump          Pump       Pump
          ↓             ↓          ↓
    ╔═══Spray══╗   ╔═Spray═╗  ╔═Spray═╗

    ████Paper Path─────────────────────→
    ↑             ↑            ↑
  Roller        Roller      Roller
    ↓             ↓            ↓
   [Catch Tray] [Tray]     [Tray]
       ↓            ↓           ↓
   (Recirculate or drain)
```

**Advantages:**
- Compact
- Easy chemistry management
- Gravity-fed drainage
- Good for desktop use

### Layout B: Vertical Processor

```
Front view:

   [Paper Stack]
        ↓
   ┌─Input Roller─┐
        ↓
   ╔═Developer═╗ ← Spray from sides
   ║ (vertical)║
   ║   Paper   ║
   ╚═══════════╝
        ↓
   ┌──Roller───┐
        ↓
   ╔═Stop Bath═╗
   ║           ║
   ╚═══════════╝
        ↓
   ┌──Roller───┐
        ↓
   ╔═══Fixer══╗
   ╚═══════════╝
        ↓
   [Output Tray]
```

**Advantages:**
- Smaller footprint
- Gravity helps drainage
- Commercial-style
- Better for sheet film

### Layout C: Single-Station Sequential

```
One processing station, chemistry changes:

    ┌─────────────────┐
    │Multi-valve system│
    │ [Dev][Stop][Fix] │
    └────────┬─────────┘
             ↓
    ╔════Spray Bar═══╗
             ↓
    ████Paper (stays still)████
             ↓
         Drain tray
             ↓
      Waste collection
```

**Process:**
1. Paper advances to station
2. Developer sprays for 60s
3. Flush with water
4. Stop bath for 30s
5. Flush
6. Fixer for 60s
7. Flush and advance to next sheet

**Advantages:**
- Simplest mechanics (one station)
- Easiest motor control (intermittent)
- Good for small batches
- Most compact

**Disadvantages:**
- Slower (sequential not continuous)
- More chemistry waste (need good flush)

## Arduino Control System

### Hardware Needed

**For Basic System:**
- Arduino Uno or Mega
- 1-2x A4988 stepper drivers (for rollers)
- 3-4x Relay modules (for pumps) - $8
- 3x 12V DC peristaltic pumps
- 12V 5A power supply
- Buttons/display for user interface (optional)

### Control Logic

```arduino
/*
 * Photo Processor Control System
 * Coordinates paper advance and chemistry pumps
 */

// Stepper pins
const int STEP_PIN = 3;
const int DIR_PIN = 2;

// Pump control (via relays)
const int PUMP_DEVELOPER = 4;
const int PUMP_STOP = 5;
const int PUMP_FIXER = 6;

// Process timing (milliseconds)
const long DEV_TIME = 60000;   // 60 seconds
const long STOP_TIME = 30000;  // 30 seconds
const long FIX_TIME = 60000;   // 60 seconds

// Paper advance (steps)
const int STEPS_PER_ZONE = 500;  // Distance between zones

void setup() {
  pinMode(STEP_PIN, OUTPUT);
  pinMode(DIR_PIN, OUTPUT);
  pinMode(PUMP_DEVELOPER, OUTPUT);
  pinMode(PUMP_STOP, OUTPUT);
  pinMode(PUMP_FIXER, OUTPUT);

  // All pumps off initially
  digitalWrite(PUMP_DEVELOPER, LOW);
  digitalWrite(PUMP_STOP, LOW);
  digitalWrite(PUMP_FIXER, LOW);

  Serial.begin(9600);
  Serial.println("Photo Processor Ready");
}

void loop() {
  Serial.println("Starting process cycle...");

  // Stage 1: Developer
  Serial.println("Developer stage");
  startPump(PUMP_DEVELOPER);
  advancePaperContinuous(DEV_TIME);  // Move slowly through dev zone
  stopPump(PUMP_DEVELOPER);

  // Brief flush (optional)
  delay(2000);

  // Stage 2: Stop bath
  Serial.println("Stop bath stage");
  startPump(PUMP_STOP);
  advancePaperContinuous(STOP_TIME);
  stopPump(PUMP_STOP);

  delay(2000);

  // Stage 3: Fixer
  Serial.println("Fixer stage");
  startPump(PUMP_FIXER);
  advancePaperContinuous(FIX_TIME);
  stopPump(PUMP_FIXER);

  // Advance to output
  Serial.println("Advancing to output");
  advancePaper(STEPS_PER_ZONE, 60);  // Fast advance

  Serial.println("Cycle complete. Waiting for next sheet...");
  delay(5000);  // Wait for operator to load next sheet
}

void startPump(int pumpPin) {
  digitalWrite(pumpPin, HIGH);
}

void stopPump(int pumpPin) {
  digitalWrite(pumpPin, LOW);
}

void advancePaper(int steps, int rpm) {
  int delayTime = (60 * 1000000L) / (200 * rpm * 2);

  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(delayTime);
  }
}

void advancePaperContinuous(long duration) {
  // Slow continuous advance during chemistry application
  int rpm = 10;  // Very slow - adjust for your paper length
  int delayTime = (60 * 1000000L) / (200 * rpm * 2);

  unsigned long startTime = millis();
  while (millis() - startTime < duration) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(delayTime);
  }
}

/*
 * ADVANCED: Variable Speed for Different Zones
 */
void processWithVariableSpeeds() {
  // Developer - slow speed (more time in chemistry)
  startPump(PUMP_DEVELOPER);
  advancePaperAtSpeed(500, 5);  // 5 RPM (very slow)
  stopPump(PUMP_DEVELOPER);

  // Quick advance to stop bath
  advancePaperAtSpeed(200, 30);  // 30 RPM

  // Stop bath - medium speed
  startPump(PUMP_STOP);
  advancePaperAtSpeed(300, 15);  // 15 RPM
  stopPump(PUMP_STOP);

  // And so on...
}

void advancePaperAtSpeed(int steps, int rpm) {
  int delayTime = (60 * 1000000L) / (200 * rpm * 2);

  for (int i = 0; i < steps; i++) {
    digitalWrite(STEP_PIN, HIGH);
    delayMicroseconds(delayTime);
    digitalWrite(STEP_PIN, LOW);
    delayMicroseconds(delayTime);
  }
}
```

## Parts List for Drizzle System

### Motors & Drivers (You Have These!)
- ✅ 1-2x Nema 17 stepper motors (from your 10-pack)
- [ ] 1-2x A4988 driver modules - $4
- [ ] 12V 5A power supply - $15

### Pumps & Plumbing
- [ ] 3x 12V peristaltic pumps (60-100ml/min) - $45 ($15 each)
  - Or: 3x aquarium pumps for budget version - $30
- [ ] Silicone tubing (6mm ID, 3 meters) - $12
- [ ] 3x Relay modules (for pump control) - $8
- [ ] Check valves (prevent backflow) - $10
- [ ] Y-connectors or manifolds - $8

### Chemistry Containers
- [ ] 3x 1-liter bottles with caps (HDPE or glass) - $15
  - Need drillable caps for tube fittings
- [ ] Tube fittings/grommets - $10
- [ ] 3x Catch trays (can be 3D printed or sheet metal) - $20

### Spray System
- [ ] PVC pipe for spray bars (1/2", 3 feet) - $5
- [ ] End caps - $3
- [ ] Drill bit (1mm) for holes - $3
- [ ] Mounting brackets - DIY or $10

### Roller System (Simplified!)
- [ ] 2-3x PVC pipe sections (20-25mm diameter) - $5
- [ ] 4-6x 608ZZ bearings - $6
- [ ] 5mm shaft rod (2 feet) - $5
- [ ] GT2 belt + pulleys - $15
  - Or O-rings for budget - $5

### Frame & Enclosure
- [ ] Aluminum extrusion or wood frame - $30
- [ ] Acrylic sheets (for splash guards) - $20
- [ ] Fasteners, brackets - $15

### Optional Upgrades
- [ ] Temperature sensors (DS18B20) - $8
  - Monitor chemistry temperature
- [ ] LCD display (16x2 or OLED) - $10
  - Show process status
- [ ] Emergency stop button - $8
- [ ] LED indicators - $5
- [ ] Water rinse system (4th pump) - $15

**Total Cost: $240-280** (vs $150-200 for full submersion roller system)

## Build Sequence

### Phase 1: Basic Paper Transport (Week 1)
1. Build simple 2-roller system
2. Get stepper motor advancing paper
3. Test with dry paper advance
4. Verify consistent speed

### Phase 2: Single Chemistry Test (Week 2)
1. Add one pump and spray bar
2. Test developer application
3. Tune flow rate and paper speed
4. Verify even coverage

### Phase 3: Full System (Week 3-4)
1. Add stop bath and fixer zones
2. Integrate all pumps
3. Wire relay controls
4. Add catch trays and drainage

### Phase 4: Refinement (Ongoing)
1. Add temperature control
2. Build enclosure
3. Add UI (buttons, display)
4. Chemistry recirculation system
5. Auto-loading mechanism

## Safety Considerations

1. **Ventilation** - Even with closed containers, provide exhaust fan
2. **Spill containment** - Secondary trays under all chemistry zones
3. **Emergency stop** - Kill all pumps and motors instantly
4. **Electrical safety** - Keep electronics away from chemistry
5. **Pump failure detection** - Monitor flow (optical sensor in tubes)
6. **Over-pressure relief** - Vent caps on chemistry containers

## Advantages Summary

**Compared to your original roller bath idea:**

| Aspect | Roller Bath | Drizzle System |
|--------|-------------|----------------|
| Motor torque needed | High ❌ | Low ✅ |
| Your motors work? | Marginal ⚠️ | Perfect ✅ |
| Chemistry volume | Large | Small ✅ |
| Chemistry life | Oxidizes fast | Better ✅ |
| Safety | Open trays ⚠️ | Closed ✅ |
| Complexity | High | Medium ✅ |
| Cost | $150-200 | $240-280 |
| Footprint | Large | Compact ✅ |

## Next Steps

1. **Read this design doc** and decide on layout (A, B, or C)
2. **Order pumps** - Start with cheap aquarium pumps to prototype
3. **Build paper transport** - Use your existing motors!
4. **Test with water first** - Perfect the mechanics before adding chemistry
5. **Add one chemistry at a time** - Don't try to build everything at once

This design plays to the strengths of your motors while creating a much more practical photo processing system!
