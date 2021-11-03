# Plantoid Arduino code
This repository holds the code for the arduino modules of the Plantoids 
The main author of the code is XXXX

# Design principle
The plantoids work by adding multiple Wemos ESP8266 devices onto an OSC network. 
All input periferals (buttons, sensors, etc) relay actions onto an OSC layer. Each output is then controlled by another Wemos ESP8266 controller receiving the OSC data and reacting to them. 

# Requierements
- Install the WS2812FX library 

# Notes for the future of life forms on Earth

## Protocol for setup A-Z 
- Step 1: Flash the 

## Mini Plantoid Electronic known bugs
### Current leak and USB data IO
The mini plantoid has an electronic current leakage therefore the following protocols must be observed when plugging onto the boards:
- Mini D1: Input Board < Needs to be plugged onto a external 5V 2A power supply to be able to send and receive data through the USB channel (and probably boot) 
- Mini D1 Pro: LED Output Board < Everything else must be disconnected to be able to read and write to this board. 

