## Fish Tank Automation

## About the Project

This project is intened to automate the process of refilling and adding water to fish tanks.  
It uses a [adafruit feather Huzzah](https://www.adafruit.com/product/2821) to control two normally closed solenoids.

## Software

The solenoid is opened by one of two way:

<ol>
  <li>A float switch that drops below the set level</li>
  <li>At the set time to cycle the tanks on a schudule</li>
</ol>
  
 In this example only tank A has a float switch but it could be added to all if the tanks if desired.

 In order to sync the time with your local time zone the [ezTime library](https://github.com/ropg/ezTime) is used.  This libary needs to be dowloaded and then included on the project.

 To connect to WiFi to allow the time synce a Config file needs to be inculded with your WiFi_SSID and Password. An example can be found [here](/include/example_Config.h)


## Built With
Built using [platformIO](https://platformio.org/) and a [adafruit feather Huzzah](https://www.adafruit.com/product/2821)


## Hardware

The circut can be seen below and the fritzing file is avalibale for [download](/arduinoCircuit/fishCycler.fzz).
![image of circuit](arduinoCircuit/fishCyclerCircuit.png?raw=true)

## License
Distributed under the MIT License. See LICENSE for more information.

## Contact
Brendan Murphy | www.brendanmurphy.xyz | brendan@thesimplekid.xyz
