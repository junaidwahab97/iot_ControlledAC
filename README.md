# iotProject
## Abstract
Coming home in hot summer days and waiting for the AC to cool the room while we sweat makes us really uneasy. To devise a method and turn on the AC from anywhere with our mobile phone would solve this problem easily. All we need is an IoT implementation and solution to the problem.
This can be achieved via two ways either using a relay to control the current to the AC or using an IR setup to control the AC through IR signals.
Every AC has a remote using IR technology to control it. What I did was use the same technology to our disposal. Capturing the IR signal from the remote and then transmitting the same signal via an IR led does the job. 
The user just needs to use a software switch via Adafruit to turn on and off the AC. All of the setup uses MQTT protocol and internet to communicate. Google assistant and Adafruit are used to run voice commands while IFTTT app is used to fuse them together.










HARDWARE REQUIRED:
•	1 * Nodemcu ESP8266 module.
•	1 * IR Receiver (TSOP1738).
•	1 * IR Led.
•	1 * NPN Transistor (2N3904).
•	1 * Breadboard
•	Jumper Wires
•	1 * 300 Ohm Resistor
•	A Computer.
•	1 * Relay Module.
•	An Android phone.

SOFTWARE REQUIRED:
•	Arduino IDE.
•	ESP8266 library.
•	IR Remote Library for ESP8266.
•	Adafruit MQTT Library.
•	Anrdoid OS.

MISCELLANEOUS:
•	WiFi Internet connection.
•	Wire cutter.
•	1 * Micro USB Cable.

TOTAL COST OF COMPONENTS:
-Rs 800-1000

## System Oveview
The main component of the setup is the Nodemcu ESP8266 module. All the other hardware components are connected   to the Nodemcu. The board is programmed in Arduino IDE and uses the ESP8266, Arduino json, adafruit and irremote esp8266 libraries. These libraries have been added to the Arduino IDE.
The neutral wire of the air conditioner is connected to the relay and the relay is connected to the Nodemcu. The IR receiver is also connected to the Nodemcu module. The transistor is connected with IR led to transmit IR signal of the required AC.

## Controlling Via Relay

•	Connect relay to D7 pin.
•	Give power via the 3.3V pin.
•	Connect an LED and 300 Ohm resistor also to circuit.
•	Setup the Nodemcu on the breadboard as shown. 

## Receiving IR Signal From AC Remote

We need to first receive the IR signal from our remote in order to replicate it. We set the remote to the required settings then press the power on and off button then capture it with the receiver. Irremoteesp8266 library is used . We can skip this step if we already have the code for our AC.
## Transmitting IR Signal
To transmit the IR signal we use an IR led and a NPN Transistor. The IR led transmits the IR signal to the AC which turns it on or off.
We have to upload the code according to our AC manufacturer.
