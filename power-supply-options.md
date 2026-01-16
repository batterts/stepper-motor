# Power Supply Options - Stepping Down 12V to 5V

## Why You Need Both 12V and 5V

Your stepper motor system needs two voltages:
- **12V** - Motor power (VMOT on A4988)
- **5V** - Logic power (VDD on A4988, Arduino)

Instead of using two separate power supplies, you can use one 12V supply and step it down to 5V.

## Option 1: Arduino's Built-in Regulator (Recommended for Beginners)

### Method A: Barrel Jack Connection

**What you need:**
- 12V power supply with 2.1mm barrel jack
- Arduino Uno

**Wiring:**
```
        12V Power Supply
              |
              ↓
    ┌───[Barrel Jack]───┐
    │                    │
    │  Arduino Uno       │
    │  (Internal 7-12V   │
    │   to 5V regulator) │
    │                    │
    │  5V pin ───────────┼──→ A4988 VDD
    │  GND ──────────────┼──→ A4988 GND
    │  Pin 2 ────────────┼──→ A4988 DIR
    │  Pin 3 ────────────┼──→ A4988 STEP
    │                    │
    └────────────────────┘
              |
              ↓
    12V also goes to A4988 VMOT
    (tap from barrel jack or use splitter)
```

**How to wire 12V to both Arduino and A4988:**

**Option A: Use Y-cable/splitter**
```
12V Supply → Y-splitter → Arduino barrel jack
                       → A4988 VMOT (via breadboard)
```

**Option B: Tap from Arduino's VIN**
```
12V Supply → Arduino barrel jack
Arduino VIN pin → A4988 VMOT
(VIN pin has the input voltage, before regulation)
```

### Method B: VIN Pin Connection

**If your power supply doesn't have a barrel jack:**

```
12V Supply (+) → Arduino VIN pin
12V Supply (–) → Arduino GND

Arduino 5V pin → A4988 VDD
Arduino GND → A4988 GND

12V Supply (+) → A4988 VMOT (directly)
12V Supply (–) → A4988 GND
```

### Specifications
- **Input voltage**: 7-12V DC (recommended range)
  - Absolute max: 20V (but generates excessive heat)
  - Your 12V supply is perfect!
- **Output current**: ~500-800mA from 5V pin
- **Regulator type**: Linear (LM1117 or similar)
- **Efficiency**: ~40-50% (rest becomes heat)

### Pros and Cons

✅ **Advantages:**
- No extra components needed
- Already built into Arduino
- Simple wiring
- Free!

⚠️ **Disadvantages:**
- Gets warm with high current draw
- Limited to ~500-800mA on 5V output
- Not efficient (wastes power as heat)
- **For 1-2 motors: FINE**
- **For 3-4+ motors: Use buck converter instead**

### When to Use This
- ✅ Testing single motor
- ✅ Simple projects (1-2 motors)
- ✅ You don't want to buy extra parts
- ❌ Running 3-4 motors continuously
- ❌ Need high efficiency (battery powered)

## Option 2: Buck Converter Module (Best for Multiple Motors)

### What It Is
A small DC-DC converter module that efficiently steps down voltage.

**Common models:**
- LM2596 (2A, most popular)
- XL4015 (5A, high power)
- MP1584 (3A, tiny size)
- LM2596S (adjustable)

**Cost:** $1-3 each on Amazon (or $0.50 on AliExpress)

### Wiring Diagram

```
    12V Power Supply
         |
         ↓
   ┌─────────────┐
   │ Buck        │
   │ Converter   │  Adjust pot to exactly 5.0V
   │ (LM2596)    │  (use multimeter)
   │             │
   │ IN+  OUT+   │
   │ IN–  OUT–   │
   └──┬────┬─────┘
      |    |
   12V|    |5V
      |    ↓
      |   Arduino 5V pin (or VIN with USB disconnected)
      |   A4988 VDD (all drivers)
      |   Common GND
      |
      ↓
   A4988 VMOT (all drivers)
   Common GND
```

### Detailed Wiring

```
Buck Converter:
  IN+ → 12V supply positive
  IN– → 12V supply negative (GND)
  OUT+ → Arduino 5V pin
       → A4988 #1 VDD
       → A4988 #2 VDD
       → A4988 #3 VDD
  OUT– → Common GND

A4988 drivers:
  VMOT → 12V supply positive (directly from supply)
  GND → Common GND
```

### Setup Procedure

1. **DO NOT connect to Arduino/A4988 yet!**

2. **Connect only the INPUT:**
   - IN+ to 12V positive
   - IN– to 12V negative

3. **Adjust output voltage:**
   - Use multimeter on OUT+ and OUT–
   - Turn adjustment pot (small screw/dial)
   - Set to exactly 5.0V
   - Clockwise = increase, counter-clockwise = decrease

4. **Verify voltage is stable:**
   - Should read 5.0V ±0.1V
   - Stable (not fluctuating)

5. **Now connect to Arduino and A4988:**
   - OUT+ to 5V pin (or VIN if USB disconnected)
   - OUT– to GND

### Specifications

**LM2596 Module (Most Common):**
- Input: 4.5V - 40V DC (12V perfect!)
- Output: 1.25V - 35V (adjustable)
- Current: 2A continuous, 3A peak
- Efficiency: 92% typical
- Size: ~43mm x 21mm x 14mm
- Switching frequency: 150 kHz

### Pros and Cons

✅ **Advantages:**
- Very efficient (~90-92%)
- Minimal heat generation
- High current capability (2-3A)
- Can power Arduino + multiple A4988 drivers
- Cheap ($1-2)
- Adjustable output voltage
- Perfect for 3-4+ motors

⚠️ **Disadvantages:**
- Need to buy separate module
- Slightly more complex wiring
- Generates electrical noise (usually not a problem)
- Need to adjust voltage before use

### When to Use This
- ✅ Running 3-4+ motors
- ✅ Want efficient power use
- ✅ Battery-powered projects
- ✅ Motors running for long periods
- ✅ Best long-term solution

### Shopping

**Amazon search terms:**
- "LM2596 DC-DC buck converter"
- "12V to 5V step down module"
- "DC-DC buck converter adjustable"

**What to buy:**
- LM2596 module (2-3A version)
- Get 2-3 units (spares + extras for future)
- Price: ~$8-12 for 5-pack

**Features to look for:**
- Adjustable pot for voltage
- LED power indicator (helpful)
- Screw terminals or header pins
- Heat sink on chip

## Option 3: Linear Regulator (LM7805)

### What It Is
Classic 3-pin voltage regulator IC that drops voltage to 5V.

### Circuit Diagram

```
           LM7805
            ┌─┐
   12V IN ──┤1├─── 5V OUT
            │ │
   GND ─────┤2│
            └─┘

With capacitors:
   12V ──┬──[0.33µF]──┬── LM7805 IN
         │            │
        GND          GND

   5V OUT ──[0.1µF]── GND
```

### Component List
- 1x LM7805 voltage regulator (~$0.50)
- 1x 0.33µF capacitor (input)
- 1x 0.1µF capacitor (output)
- 1x Heat sink (essential for >300mA)
- Thermal paste
- Perfboard or breadboard

### Specifications
- Input: 7-35V DC (12V works)
- Output: 5V ±5% (fixed)
- Current: 1A max (with good heat sink)
- Dropout voltage: ~2V (needs at least 7V input)
- Efficiency: ~40% at 12V input

### Heat Dissipation

**Power dissipated as heat:**
```
Heat (Watts) = (Vin - Vout) × Current
             = (12V - 5V) × Current
             = 7V × Current

At 500mA: 3.5W of heat! 🔥
At 1A: 7W of heat! 🔥🔥
```

**You MUST use a heat sink for >300mA!**

### Pros and Cons

✅ **Advantages:**
- Very simple circuit
- Cheap ($0.50)
- Fixed 5V output (no adjustment needed)
- No electrical noise
- Reliable

⚠️ **Disadvantages:**
- Very inefficient (~40%)
- Generates lots of heat
- Needs large heat sink for high current
- Limited to 1A max
- Wastes power (bad for battery projects)

### When to Use This
- ✅ Low current needs (<300mA)
- ✅ You have parts on hand
- ✅ Need noise-free power
- ❌ Multiple motors (too hot)
- ❌ Battery powered (wastes power)
- ❌ Don't use this for your project - buck converter is better!

## Comparison Table

| Feature | Arduino Regulator | Buck Converter | LM7805 Linear |
|---------|-------------------|----------------|---------------|
| **Cost** | Free (built-in) | $1-2 | $0.50 + heat sink |
| **Efficiency** | 40-50% | 90-92% | 40% |
| **Max Current** | 500-800mA | 2-3A | 1A (with heat sink) |
| **Heat** | Warm | Cool | Very hot |
| **Complexity** | ⭐ (easiest) | ⭐⭐ (easy) | ⭐⭐⭐ (medium) |
| **Best for** | 1-2 motors | 3-4+ motors | Low current only |
| **Adjustable?** | No (5V fixed) | Yes | No (5V fixed) |

## Recommended Setup by Project Size

### Single Motor Test Project
```
12V Supply → Arduino Barrel Jack → Built-in regulator
           ↘ A4988 VMOT (12V)
Arduino 5V → A4988 VDD
```
**Use:** Arduino's built-in regulator ✅

### Photo Booth with 1 Motor + 3 Pumps (4 motors total)
```
12V Supply → Buck Converter → 5V out
           ↘                  ↘ Arduino 5V
            ↘                  ↘ All A4988 VDD pins
             ↘ All A4988 VMOT pins (12V)
```
**Use:** Buck converter module ✅

### Future: Battery-Powered Sun Tracker
```
12V Battery → Buck Converter → 5V (efficient!)
            ↘ Motor VMOT
```
**Use:** Buck converter (saves battery) ✅

## Wiring Example: Buck Converter with Multiple Motors

```
                    12V 5A Power Supply
                         |
            ┌────────────┴────────────┐
            |                         |
            |                         |
       ┌────▼────┐              ┌─────▼─────┐
       │  Buck   │              │ A4988 #1  │
       │Converter│              │  VMOT     │
       │ LM2596  │              └───────────┘
       │         │              ┌───────────┐
       │ OUT: 5V │──────┬───────│ A4988 #2  │
       └─────────┘      │       │  VMOT     │
                        │       └───────────┘
                        │       ┌───────────┐
                        │       │ A4988 #3  │
                        │       │  VMOT     │
                        │       └───────────┘
                        │       ┌───────────┐
                        │       │ A4988 #4  │
                        │       │  VMOT     │
                        │       └───────────┘
                        │
                        ├───────→ Arduino 5V pin
                        ├───────→ A4988 #1 VDD
                        ├───────→ A4988 #2 VDD
                        ├───────→ A4988 #3 VDD
                        └───────→ A4988 #4 VDD

All GND connected together (common ground)
```

## Safety Notes

⚠️ **Important:**
- Always use common ground between all components
- Don't connect USB and external 5V simultaneously to Arduino
  - Either: USB for programming (no external 5V)
  - Or: External 5V (unplug USB)
- Match power supply current to your needs:
  - 1 motor: 2A supply minimum
  - 4 motors: 5A supply minimum
- Add capacitors near A4988 drivers (100µF) for stability
- Don't exceed 12V for your motors (rated max)

## What to Buy for Your Project

### Starting Out (1 motor test):
- ✅ 12V 2A power supply with barrel jack
- ✅ Nothing else needed (use Arduino regulator)

### Building Photo Booth (4 motors):
- ✅ 12V 5A power supply
- ✅ LM2596 buck converter (5-pack for $10)
- ✅ Wire/connectors for distribution
- Optional: Power distribution board

### Amazon Shopping List

**For testing (1-2 motors):**
- 12V 2A power supply with barrel jack (~$10)
```
Search: "12V 2A power adapter 2.1mm"
```

**For full project (3-4 motors):**
- 12V 5A power supply (~$15)
```
Search: "12V 5A power supply"
```
- LM2596 buck converter modules (~$10 for 5)
```
Search: "LM2596 DC-DC buck converter 5 pack"
```
- Optional: DC power splitter cables (~$8)
```
Search: "DC power splitter 2.1mm"
```

## My Recommendation

**For your first test:**
Use Arduino's built-in regulator (Option 1). It's free and simple.

**When you expand to 3-4 motors for photo booth:**
Add a buck converter module (Option 2). Much more efficient and reliable.

**Don't bother with LM7805** unless you already have one - buck converters are better in every way.

## Next Steps

1. **For now**: Use Arduino barrel jack with 12V supply
2. **Order for later**: LM2596 buck converter 5-pack ($10)
3. **Test single motor** with simple power setup
4. **Upgrade power** when adding multiple motors

Questions? Check the repo or ask!
