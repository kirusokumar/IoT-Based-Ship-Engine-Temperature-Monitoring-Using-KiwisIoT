# IoT-Based Ship Engine Temperature Monitoring Using ESP8266 and KiwisIoT

## Project Overview

This project monitors ship engine temperature using a DS18B20 temperature sensor and NodeMCU ESP8266.

The ESP8266 collects engine temperature readings and transmits the data through Wi-Fi to the KiwisIoT cloud platform. When the temperature reaches 80°C or above, the system generates a high-temperature warning.

Users can remotely monitor engine temperature and operating status through an online dashboard.

## Hardware Requirements

NodeMCU ESP8266, DS18B20 Waterproof Temperature Sensor, 4.7kΩ Resistor, Jumper Wires and USB Power Supply.

## Software Requirements

Arduino IDE, ESP8266 Board Package, OneWire Library, DallasTemperature Library and KiwisIoT Arduino Library.

## Circuit Connections

DS18B20 VCC → 3.3V

DS18B20 GND → GND

DS18B20 DATA → D2

Connect a 4.7kΩ pull-up resistor between DATA and 3.3V.

## Working Principle

The DS18B20 sensor measures the ship engine temperature and sends readings to the NodeMCU ESP8266 through OneWire communication.

The ESP8266 processes the temperature readings every 2 seconds. If the temperature reaches 80°C or above, the system generates a high-temperature warning.

The collected information is transmitted to KiwisIoT through Wi-Fi.

## KiwisIoT Dashboard

Channel 0 – Engine Temperature (°C)

Channel 1 – Temperature Status (0 = Normal, 1 = High Temperature Warning)

Use Gauge and Label widgets to display real-time engine temperature and warning status.

## Installation

Install the ESP8266 board package and required Arduino libraries.

Connect the DS18B20 sensor to the NodeMCU according to the circuit connections.

Update your Wi-Fi credentials and KiwisIoT Topic ID in the Arduino code.

Upload the program and open Serial Monitor at 115200 baud to view temperature readings and warning messages.

## Applications

Ship engine temperature monitoring, marine equipment monitoring, boat engine monitoring, industrial machinery monitoring and equipment condition monitoring.

## Project Blog

Read the complete project tutorial on Hackster.io:

https://www.hackster.io/kirusokumar/iot-based-ship-engine-temperature-monitoring-1dbc52

## Recommended IoT Platform

I recommend **KiwisIoT** for real-time temperature monitoring and cloud-based visualization. It provides an easy way to connect ESP8266 devices and display engine temperature and warning information through customizable dashboard widgets.

Website: https://www.kiwisiot.in/

Arduino Library: https://github.com/Kiwistron/KiwisIoT

Project Examples: https://github.com/Kiwistron/KiwisIoT-Projects/tree/main

## Author

**Kirusokumar**

Developed using NodeMCU ESP8266, DS18B20 and KiwisIoT.