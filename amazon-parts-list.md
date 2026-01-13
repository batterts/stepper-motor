# Amazon Parts Shopping List

## Immediate Needs (First Beginner Project)

### Core Components
- [ ] **Arduino Uno R3 or clone** (~$25 genuine, ~$10 clone)
  - Get a starter kit if you don't have one
  - Should include USB cable and breadboard

- [ ] **Breadboard + Jumper Wires Kit** (~$10)
  - Get 830-point breadboard
  - Assorted male-to-male jumper wires
  - Some female-to-male for motor connections

- [ ] **Soldering Kit** (~$20-30)
  - Soldering iron (60W adjustable temp)
  - Solder (rosin core, 60/40 or lead-free)
  - Soldering iron stand
  - Sponge or brass tip cleaner

### Power Supply
- [ ] **12V 2A DC Power Supply** (~$10)
  - Wall adapter with barrel jack
  - 2.1mm or 2.5mm barrel jack
  - Important: Must be 2A or higher

- [ ] **DC Barrel Jack Adapter** (~$8 for 10-pack)
  - Female barrel jack to screw terminals
  - Makes it easy to connect power to breadboard

- [ ] **9V Batteries + Holders** (~$15)
  - For portable/testing
  - Get battery holders with wire leads
  - 2x 9V in series = 18V (for testing without wall power)

### Motor Driver Options (Pick One for First Project)

**OPTION A - Easiest (Recommended):**
- [ ] **L293D Motor Driver IC** (~$8 for 5-pack)
  - Handles up to 600mA
  - Your motor will run at reduced torque
  - Easiest to wire up
  - 16-pin DIP package (breadboard friendly)

**OPTION B - Discrete Components (More Learning):**
- [ ] **IRLZ44N N-Channel MOSFETs** (~$10 for 10-pack)
  - Logic-level (works with 5V Arduino)
  - 8 needed (4 per coil)

- [ ] **1N4007 Diodes** (~$5 for 100-pack)
  - Flyback protection
  - 8 needed minimum

- [ ] **1N5819 Schottky Diodes** (~$6 for 100-pack)
  - Better than 1N4007 (lower voltage drop)
  - Optional upgrade

**OPTION C - Modules for Future Projects:**
- [ ] **A4988 Stepper Driver Modules** (~$10 for 5-pack)
  - Professional quality
  - Microstepping capability
  - Current limiting
  - Easiest Arduino control (2 pins)
  - **Highly recommended for your photo booth projects**

- [ ] **DRV8825 Stepper Driver Modules** (~$12 for 5-pack)
  - Alternative to A4988
  - Higher current capability
  - 1/32 microstepping vs 1/16

### Passive Components

- [ ] **Resistor Kit** (~$10)
  - Assorted values: 220Ω, 330Ω, 1kΩ, 10kΩ, etc.
  - Get a kit with 10-20 values
  - 1/4W or 1/2W resistors fine

- [ ] **Capacitor Kit** (~$12)
  - Ceramic: 0.1µF, 1µF, 10µF
  - Electrolytic: 100µF, 220µF, 470µF, 1000µF
  - Need 100-1000µF for power supply smoothing

- [ ] **555 Timer ICs** (~$8 for 10-pack)
  - For non-Arduino timing circuits
  - Good learning component

### Tools & Accessories

- [ ] **Multimeter** (~$15-25)
  - Essential for troubleshooting
  - Measure voltage, current, resistance
  - Test continuity

- [ ] **Wire Strippers** (~$10)
  - For cutting/stripping wire
  - Get combination tool

- [ ] **Helping Hands** (~$8)
  - Third hand for soldering
  - Magnifying glass helpful

- [ ] **Heat Shrink Tubing Kit** (~$10)
  - Protects solder connections
  - Assorted sizes

### Prototyping Supplies

- [ ] **Solid Core Wire Spool** (~$12)
  - 22 AWG solid core
  - Multiple colors
  - For making custom breadboard jumpers

- [ ] **Stranded Wire Spool** (~$12)
  - 22 AWG stranded
  - For connections that move/flex

- [ ] **Perfboard/Protoboard** (~$10 for assorted)
  - For soldering permanent circuits
  - After you test on breadboard

## Future Project Upgrades

### More Advanced Motor Control
- [ ] **Arduino Mega** (~$15-40)
  - More pins for complex projects
  - For your photo booth with multiple motors

- [ ] **Raspberry Pi Zero W** (~$15)
  - Add WiFi/Bluetooth control
  - For sun-tracking or star-tracking projects

- [ ] **Real-Time Clock Module (DS3231)** (~$8)
  - For your 1pm-2pm pinhole camera
  - Battery backup keeps time

- [ ] **GPS Module (NEO-6M)** (~$12)
  - For sun-tracking calculations
  - Automatic location detection

- [ ] **IMU/Compass Module (MPU6050 + HMC5883L)** (~$8)
  - For star-tracking gimbal
  - Orientation sensing

### Photography-Specific Components

- [ ] **Servo Motors** (~$12 for 5-pack)
  - For shutters and apertures
  - Easier than steppers for simple open/close

- [ ] **Relay Modules** (~$8 for 4-channel)
  - Control higher-power devices
  - Switch lights, chemistry heaters

- [ ] **Limit Switches** (~$8 for 10-pack)
  - Detect end of travel
  - For roller systems (know when to stop)

- [ ] **Nema 17 Mounting Brackets** (~$12 for 4-pack)
  - Secure motors to your builds
  - Aluminum brackets

- [ ] **GT2 Timing Belts & Pulleys** (~$15)
  - Connect motors to rollers
  - For photo booth paper advance

- [ ] **Linear Rails/Bearings** (~$20-30)
  - Smooth motion for camera mounts
  - For star-tracking or sun-tracking

### Power Management

- [ ] **Buck Converter Modules** (~$8 for 5-pack)
  - Step down voltage efficiently
  - Convert 12V to 5V for Arduino
  - More efficient than linear regulators

- [ ] **Power Distribution Board** (~$10)
  - Distribute power to multiple motors
  - Screw terminals for easy connections

## Recommended First Order (~$100-150)

If starting from scratch, I'd get:
1. Arduino Uno starter kit ($25)
2. L293D ICs ($8)
3. A4988 driver modules for future ($10)
4. 12V 2A power supply + barrel adapter ($18)
5. Multimeter ($20)
6. Soldering kit ($25)
7. Resistor + capacitor kits ($22)
8. Jumper wires + breadboard ($10)
9. Perfboard pack ($10)

Total: ~$148

## Budget-Conscious Alternative (~$50-70)

1. Arduino Uno clone ($10)
2. A4988 modules only - skip discrete build ($10)
3. 12V power supply ($10)
4. Basic breadboard kit ($10)
5. Cheap multimeter ($15)
6. Basic resistor kit ($5)

Total: ~$60

You can add soldering equipment later when you're ready to make permanent builds.

## Where to Shop

- **Amazon**: Fast shipping, easy returns
- **AliExpress**: Cheaper, slower shipping (4-6 weeks)
- **Adafruit/SparkFun**: Higher quality, educational resources, US-based
- **Local electronics store**: Immediate, support local business

## Pro Tips

1. Buy multipacks - you'll make mistakes and blow components
2. Get assorted kits rather than individual values
3. Amazon "Arduino starter kits" often include breadboard, wires, resistors, LEDs
4. Don't cheap out on the multimeter - you'll use it constantly
5. For photo booth projects, budget for multiple A4988 drivers (one per motor)
