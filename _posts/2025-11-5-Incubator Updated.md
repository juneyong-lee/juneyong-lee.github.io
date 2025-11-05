---
layout: post
title: "Making #4; Incubator Updated"
---



<BR>
[Arduino code](https://github.com/juneyong-lee/juneyong-lee.github.io/blob/master/projects/making/incubator/Incubatorupdated.ino)<BR>

<BR>
<BR>
    
![]({{ juneyong-lee.github.io }}/images/Incubator_bb2.jpg) <BR>

12V Adapter (+)  ──>  Inline 5A Fuse  ──>  CS707025Z (NC @ 70°C)  ──>  PCB( +12V)<BR>
12V Adapter (–) ─────────────────────────────────>  PCB (GND)<BR>
<BR>
Heater Channel (MOSFET IRLB8721)<BR>
Q1 Gate   ──>  D10 via 100 Ω series resistor (RgH) + 100 kΩ pull-down (RpH) Gate→Source<BR>
Q1 Drain  ──>  HEAT−<BR>
Q1 Source ──>  GND plane (common)<BR>
<BR>
Fan Channel (MOSFET P36NF06L)<BR>
Q2 Gate   ──>  D11 via 100 Ω series resistor (RgF) + 100 kΩ pull-down (RpF) Gate→Source<BR>
Q2 Drain  ──>  FAN−<BR>
Q2 Source ──>  GND plane (common)<BR>
<BR>
Mini Step Down Module<BR>
HW-613 VOUT+  ──>  5V+<BR>
HW-613 VOUT−  ──> GND<BR>
HW-613 VIN+ ──> 12V+<BR>
HW-613 VIN− ──> GND<BR>
<BR>
Arduino Uno<BR>
GND  ──>  GND plane<BR>
5V   ──>  5V bus<BR>
<BR>
DHT22 Sensor (Air Temp)<BR>
DHT22 VCC  ──>  5V<BR>
DHT22 GND  ──>  GND<BR>
DHT22 DATA ──>  Arduino D6<BR>
<BR>
Quad Alphanumeric Display (Adafruit 0.54″ I²C)<BR>
SDA → Arduino A4<BR>
SCL → Arduino A5<BR>
VCC → 5V<BR>
GND → GND<BR>
<BR>
Rotary Encoder<BR>
Encoder A → Arduino D2<BR>
Encoder B → Arduino D3<BR>
Encoder GND → GND<BR>
<BR>
<BR>


The original incubator design came from [this instruction.](http://biohackacademy.github.io/bha6/class/3) 
