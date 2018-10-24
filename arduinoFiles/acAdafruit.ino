/***************************************************
  Adafruit MQTT Library ESP8266 Example

  Must use ESP8266 Arduino from:
    https://github.com/esp8266/Arduino

  Works great with Adafruit's Huzzah ESP board & Feather
  ----> https://www.adafruit.com/product/2471
  ----> https://www.adafruit.com/products/2821

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Tony DiCola for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
#ifndef UNIT_TEST
#include <Arduino.h>
#endif
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ESP8266WiFi.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

/************************* WiFi Access Point *********************************/

#define WLAN_SSID       "VGN 329"
#define WLAN_PASS       "hhr28jj97"

/************************* Adafruit.io Setup *********************************/

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883                   // use 8883 for SSL
#define AIO_USERNAME    "junaidwahab97"
#define AIO_KEY         "4a8f8c46321b4dc49998eac2bd926d77"

/************ Global State (you don't need to change this!) ******************/



const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);  // Set the GPIO to be used to sending the message.

// Example of data captured by IRrecvDumpV2.ino
uint16_t rawData[299] = {4384, 4402,  526, 1626,  530, 544,  530, 1622,  530, 1622,  530, 546,  526, 548,  530, 1620,  532, 544,  532, 544,  530, 1622,  530, 544,  530, 544,  530, 1622,  528, 1624,  530, 546,  530, 1622,  530, 546,  528, 1622,  530, 544,  530, 1622,  530, 1622,  554, 1598,  530, 1620,  554, 1596,  530, 1622,  554, 522,  554, 1598,  552, 520,  556, 520,  554, 520,  530, 546,  554, 520,  554, 520,  530, 1622,  554, 520,  530, 1622,  554, 522,  528, 546,  530, 546,  528, 548,  554, 1596,  554, 520,  554, 1600,  528, 546,  530, 1620,  554, 1598,  530, 1622,  530, 1622,  530, 5218,  4412, 4378,  530, 1622,  530, 544,  530, 1622,  530, 1622,  530, 544,  530, 544,  530, 1620,  530, 544,  530, 544,  530, 1622,  530, 544,  530, 546,  524, 1626,  530, 1620,  532, 544,  530, 1622,  530, 546,  526, 1626,  530, 544,  530, 1620,  530, 1622,  524, 1628,  526, 1626,  524, 1626,  530, 1622,  526, 550,  524, 1628,  524, 550,  528, 546,  528, 546,  530, 546,  526, 548,  528, 546,  524, 1626,  524, 550,  528, 1624,  530, 544,  524, 552,  524, 550,  524, 552,  524, 1626,  524, 550,  524, 1626,  526, 550,  528, 1622,  524, 1626,  528, 1624,  524, 1628,  524, 5226,  4382, 4406,  524, 1628,  524, 1628,  522, 552,  528, 1622,  528, 548,  528, 1624,  530, 544,  528, 1624,  530, 546,  530, 546,  530, 1600,  550, 1620,  530, 1622,  530, 1620,  524, 552,  524, 550,  524, 550,  530, 546,  524, 550,  530, 546,  526, 548,  530, 544,  530, 544,  532, 544,  524, 548,  524, 552,  530, 544,  530, 544,  530, 544,  530, 544,  532, 544,  528, 340,  736, 544,  530, 544,  532, 544,  530, 546,  530, 544,  530, 544,  530, 546,  528, 546,  530, 544,  530, 544,  526, 550,  530, 1620,  530, 544,  530, 544,  530, 544,  530, 1620,  524};
uint16_t rawData2[199] = {4378, 4412,  524, 1628,  524, 552,  522, 1630,  522, 1628,  522, 554,  522, 552,  522, 1630,  524, 550,  522, 534,  566, 1604,  548, 526,  550, 500,  576, 1600,  552, 1598,  552, 522,  552, 1574,  578, 522,  552, 1600,  552, 1598,  554, 1598,  552, 1576,  576, 522,  554, 1598,  554, 1598,  552, 1598,  554, 520,  554, 522,  554, 520,  554, 520,  554, 1598,  554, 522,  552, 522,  552, 1598,  554, 1596,  554, 1596,  556, 520,  556, 518,  554, 520,  554, 520,  552, 522,  552, 462,  614, 520,  554, 522,  554, 1596,  554, 1598,  554, 1598,  554, 1598,  554, 1596,  556, 5194,  4408, 4380,  554, 1596,  554, 522,  554, 1596,  554, 1598,  554, 522,  554, 520,  554, 1598,  552, 522,  554, 522,  554, 1598,  554, 520,  554, 524,  552, 1576,  576, 1596,  554, 460,  614, 1598,  552, 522,  552, 1600,  550, 1576,  576, 1600,  550, 1602,  548, 528,  524, 1628,  520, 1630,  522, 1630,  522, 554,  520, 552,  522, 554,  522, 552,  522, 1584,  594, 526,  524, 552,  520, 1630,  522, 1628,  524, 1628,  520, 554,  520, 554,  522, 552,  500, 576,  518, 556,  522, 552,  520, 556,  520, 552,  522, 1628,  520, 1632,  522, 1606,  544, 1630,  522, 1630,  522};

int mystate;

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;
// or... use WiFiFlientSecure for SSL
//WiFiClientSecure client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

/****************************** Feeds ***************************************/

// Setup a feed called 'photocell' for publishing.
// Notice MQTT paths for AIO follow the form: <username>/feeds/<feedname>
//Adafruit_MQTT_Publish photocell = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/photocell");

// Setup a feed called 'onoff' for subscribing to changes.
Adafruit_MQTT_Subscribe onoffbutton = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/ac");

/*************************** Sketch Code ************************************/

// Bug workaround for Arduino 1.6.6, it seems to need a function declaration
// for some reason (only affects ESP8266, likely an arduino-builder bug).
void MQTT_connect();

void setup() {
  irsend.begin();
  Serial.begin(115200, SERIAL_8N1, SERIAL_TX_ONLY);
  Serial.begin(115200);
  delay(10);
  
  Serial.println(F("Adafruit MQTT demo"));

  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);

  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.println("WiFi connected");
  Serial.println("IP address: "); Serial.println(WiFi.localIP());

  // Setup MQTT subscription for onoff feed.
  mqtt.subscribe(&onoffbutton);
  pinMode(D7,OUTPUT);
}

uint32_t x=0;

void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();

  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here
  

  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton.lastread);
      int state = atoi((char *)onoffbutton.lastread);
      digitalWrite(D7,state);
      mystate=state;
    }
    if(mystate==1)
    {
      irsend.sendRaw(rawData, 299, 38);
      }
      else
      {
        irsend.sendRaw(rawData2, 199, 38);
        }
  }

  // Now we can publish stuff!
 /* Serial.print(F("\nSending photocell val "));
  Serial.print(x);
  Serial.print("...");
  if (! photocell.publish(x++)) {
    Serial.println(F("Failed"));
  } else {
    Serial.println(F("OK!"));
  }*/

  // ping the server to keep the mqtt connection alive
  // NOT required if you are publishing once every KEEPALIVE seconds
  /*
  if(! mqtt.ping()) {
    mqtt.disconnect();
  }
  */
}

// Function to connect and reconnect as necessary to the MQTT server.
// Should be called in the loop function and it will take care if connecting.
void MQTT_connect() {
  int8_t ret;

  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }

  Serial.print("Connecting to MQTT... ");

  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}
