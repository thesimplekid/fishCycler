## Fish Tank Automation

## About the Project

This project is intened to automate the process of refilling and adding water to fish tanks.  
It uses a [adafruit feather Huzzah](https://www.adafruit.com/product/2821) to control two normally closed solinoids.

The solenoid is opened by one of two way:

<ol>
  <li>A float switch that drops below the set level</li>
  <li>At the set time to cycle the tanks on a schudule</li>
</ol>
  
 In this example only tank A has a float switch but it could be added to all if the tanks if desired.

## Built With
<ol>
  <li>[platformIO](https://platformio.org/)</li>
  <li>[adafruit feather Huzzah](https://www.adafruit.com/product/2821)</li>
</ol>

## Hardware

The circut can be seen below and the fritzing file is avalibale for [download](/arduinoCircuit/fishCycler.fzz).
![image of circuit](arduinoCircuit/fishCyclerCircuit.png?raw=true)

## License
Distributed under the MIT License. See LICENSE for more information.

## Contact
Brendan Murphy | www.brendanmurphy.xyz | brendan@thesimplekid.xyz
