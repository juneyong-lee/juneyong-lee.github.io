---
layout: post
title: Incubator
---

![]({{ juneyong-lee.github.io }}/images/Incubator1.jpg) <BR> 


<BR>
Materials
- Insulated Foam Shipper, Medium, 17" Length x 10" Width x 8-1/4" Depth [Amazon](https://www.amazon.com/gp/product/B007PB39SW/)
- Cooling Fan, 40 x 40 x 28mm, 12V DC, 2.8 W [Amazon](https://www.amazon.com/gp/product/B075V3BYR7/) 
- Heating Element AC DC 12V Aluminum Shell Ceramic Heating Plate (220℃ 5—28W) [Amazon](https://www.amazon.com/gp/product/B07GBNGB4L)
- Aluminum Heat Sink for Raspberry Pi 3 - 15 x 15 x 15mm, 4 of them [Adafruit](https://www.adafruit.com/product/3082)
- N-channel power MOSFET - 30V / 60A [Adafruit](https://www.adafruit.com/product/355)
- Rotary encoder with switch EC11 Audio digital potentiometer 20mm handle [Ebay](https://www.ebay.com/itm/2pcs-Rotary-encoder-with-switch-EC11-Audio-digital-potentiometer-20mm-handle/311425031990?ssPageName=STRK%3AMEBIDX%3AIT&_trksid=p2060353.m1438.l2649)
- Potentiometer Volume Control Rotary Knobs, 19.5x11.5mm, 6mm Shaft Hole [Amazon](https://www.amazon.com/gp/product/B07K33QBPQ/ref=ppx_yo_dt_b_asin_title_o00_s03?ie=UTF8&psc=1)
- DHT22 temperature-humidity sensor + extras [Adafruit](https://www.adafruit.com/product/385)
- Quad Alphanumeric Display - 0.54" Digits w/ I2C Backpack, Red and Yellow [Adafruit](https://www.adafruit.com/product/1911)
- Rocker Switch, 16A 125V (450-1810-ND) [Digikey](https://www.digikey.com/product-detail/en/te-connectivity-alcoswitch-switches/PRASA1-16F-BB0BW/450-1810-ND/529580)
- Power Jack 2.1X5.5MM SOLDER (839-1291-ND) [Digikey](https://www.digikey.com/product-detail/en/tensility-international-corp/54-00063/839-1291-ND/6206244)
- Power Adapter DC 12V 3A, 36W Max [Amazon](https://www.amazon.com/gp/product/B07G47GFGV/) 
- LM2596 Step Down Module [ebay](https://www.ebay.com/itm/LM2596S-Step-Down-Module-DC-3V-40V-to1-5v-35V-3-3V-5V-12V-3A-Voltage-Regulator/173427982213)
- Plain Expanded Metal Sheet, 24 in. x 1/2 in. x 12 in. [Homedepot](https://www.homedepot.com/p/Everbilt-24-in-x-1-2-in-x-12-in-Plain-Expanded-Metal-Sheet-801417/204225783)
- PureBond Birch Plywood 1/4 in x 4 ft x 8 ft (actual 5mm thick) [Homedepot](https://www.homedepot.com/p/Columbia-Forest-Products-1-4-in-x-4-ft-x-8-ft-PureBond-Birch-Plywood-165891/100092485)

<BR>


![]({{ juneyong-lee.github.io }}/images/Incubator2.jpg) <BR> 

![]({{ juneyong-lee.github.io }}/images/Incubator_bb.jpg) <BR>


<BR>

Main Compartment
<BR>
This insulated foam shipping container holds heat very well. I was going to make a door with clear acrylic sheet but using the cover it came with was the best way to retain the heat inside. The low heat setting on my hot glue gun worked well when attaching rails for shelves, while the high setting melted the foam. I used an expanded metal sheet as shelf but sometimes it got too hot. I may change it to plastic shelf instead.

![]({{ juneyong-lee.github.io }}/images/Incubator8.jpg) <BR> 

<BR>

Heating Element
<BR>
40mm cooling fan(12v, 2.8W) runs very fast and loud. In order to slow it down, LM2596 Step Down Module is used to drop down the voltage to about 9v and it is directly connected to 12v DC power source. I plan to use another MOSFET to vary the fan speed depending on temperature. Four aluminum heat sinks are attached to the heating element to dissipate the heat faster and it's been very effective. The ground of heat element is connected to the drain of MOSTFET. Depending on the temperature, Arduino can control it from 0 to 255.

![]({{ juneyong-lee.github.io }}/images/Incubator4.jpg) <BR>

![]({{ juneyong-lee.github.io }}/images/Incubator5.jpg) <BR>
  
<BR>
  
Thermometer
<BR>
DHT22 is a reliable thermometer. More information and its tutorial on [Adafruit’s page.](https://learn.adafruit.com/dht) The left pin goes to Arduino 5v. The second pin goes to Arduino D6 and the right pin goes to ground. 10K resistor connects between 5v and signal of DHT22.

![]({{ juneyong-lee.github.io }}/images/Incubator7.jpg) <BR>

<BR>
 
Control Box
<BR>
It’s attached to the right side of the incubator and there is a small hole for wires. Red and Yellow Quad Alphanumeric Displays are connected to one I2C Backpack from Adafruit. Its tutorial is available on their [site.](https://learn.adafruit.com/adafruit-led-backpack/0-54-alphanumeric) The backpack’s VCC and Vi2c connected to Arduino 5v, CLK to A5, DAT to A4 pin of Arduino, and GND is to the common ground. The red display shows the current temperature that comes from DHT22 and the yellow shows a target temperature that can be set with rotary encoder. If current temp is higher than the target, MOSTFET sends 0 to the heating element. If target is set higher than the current, then MOSTFET send up to 255 depending on the temperature differences. The rotary encoder’s pin A goes to Arduino D2 and pin B goes to D3. The ground pin goes to the common ground. 

![]({{ juneyong-lee.github.io }}/images/Incubator3.jpg) <BR>
 
![]({{ juneyong-lee.github.io }}/images/Incubator4.jpg) <BR>

<BR>

Because the heating element uses up to 28W, sometimes MOSTFET got dangerously hot and melted a breadboard and jumper cable. When I used a PCB board for final version, I made sure to use wires that can handle higher wattage and temperature. At the same time, I plan to use some of the safety measures such as a temperature activated kill switch.

![]({{ juneyong-lee.github.io }}/images/Incubator10.jpg) <BR>

<BR>
The original incubator design came from [this instruction.](http://biohackacademy.github.io/bha6/class/3) 
