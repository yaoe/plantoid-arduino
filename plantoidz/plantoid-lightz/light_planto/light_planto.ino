/*---------------------------------------------------------------------------------------------

  Open Sound Control (OSC) library for the ESP8266

  Example for receiving open sound control (OSC) bundles on the ESP8266
  Send integers '0' or '1' to the address "/led" to turn on/off the built-in LED of the esp8266.

  This example code is in the public domain.

--------------------------------------------------------------------------------------------- */
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>
#include <OSCBundle.h>
#include <OSCData.h>
char ssid[] = "Chateau_du_Fey";          // your network SSID (name)
char pass[] = "laviedechateau";                    // your network password
WiFiUDP Udp;
const IPAddress outIp;        // remote IP (not needed for receive)
const unsigned int outPort = 9999;          // remote port (not needed for receive)
const unsigned int localPort = 9999;        // local port to listen for UDP packets (here's where we send the packets)
OSCErrorCode error;

unsigned int ledState3 = LOW; 
unsigned int ledState4 = LOW; 
unsigned int ledState5 = LOW; 
unsigned int ledState7 = LOW;              

int RUN0 = 0 ;
int RUN1 = 0 ;

int btnState0 = 0 ;
int btnState1 = 0 ;

int speedValue= 200;
int brightValue=200;
int colorValue= 1;
unsigned long setcolor = 0xFF2050;

//int8_t IP1;
//int8_t IP2;
//int8_t IP3;
//int8_t IP4;

#include <WS2812FX.h>
#define LED_PIN    D3  // digital pin used to drive the LED strip
#define LED_PIN_2    D4  // digital pin used to drive the LED strip

#define PETAL_LED_COUNT 8  // number of LEDs on the petals
#define LED_COUNT 48  // number of LEDs on the strip

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
WS2812FX ws2812fx_2 = WS2812FX(LED_COUNT, LED_PIN_2, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  ws2812fx.init();
  ws2812fx.setBrightness(100);
  ws2812fx.setSpeed(200);
  ws2812fx.setMode(FX_MODE_RAINBOW_CYCLE);
  ws2812fx.start();

  ws2812fx_2.init();
  ws2812fx_2.setBrightness(100);
  ws2812fx_2.setSpeed(200);
  ws2812fx_2.setMode(FX_MODE_RAINBOW_CYCLE);
  ws2812fx_2.start();

  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
     Serial.print(".");
  }
//  IPAddress ip(10,3,141,201);   
//  IPAddress gateway(10,3,141,1);
//  IPAddress subnet(255,255,0,0);   
//  WiFi.config(ip, gateway, subnet);
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("Starting UDP");
  Udp.begin(localPort);
  Serial.print("Local port: ");
  Serial.println(Udp.localPort());  
}
void analog0(OSCMessage &msg) {                                             // sparkel global
  btnState0 = msg.getInt(0);
  
   if(btnState0 == 1024){
   if(RUN0 == 0){ 
      ws2812fx.setMode(FX_MODE_SPARKLE);
      ws2812fx_2.setMode(FX_MODE_SPARKLE);
   RUN0 = 1;
   }else{
      ws2812fx.setMode(FX_MODE_STATIC);
      ws2812fx_2.setMode(FX_MODE_STATIC);
   RUN0 = 0;        
   }
   }  
}
void analog1(OSCMessage &msg) {                                                // change effets pistils
btnState1 = msg.getInt(0);
   if(btnState1 == 1024){
   if(RUN1 == 0){
      ws2812fx.setMode(FX_MODE_COMET);
      ws2812fx_2.setMode(FX_MODE_COMET);
      ws2812fx.setSpeed(speedValue);
      ws2812fx_2.setSpeed(speedValue);
   RUN1 = 1;
   }else{
      ws2812fx.setMode(FX_MODE_STATIC);
      ws2812fx_2.setMode(FX_MODE_STATIC);
      ws2812fx.setSpeed(speedValue);
      ws2812fx_2.setSpeed(speedValue);
   RUN1 = 0;        
   }
   }  
   }
void analog2(OSCMessage &msg) {
// code here  
}
void analog3(OSCMessage &msg) {
  ledState3 = msg.getInt(0);
  brightValue = map(ledState3, 254, 1024, 0, 255);
  ws2812fx.setBrightness(brightValue);
  ws2812fx_2.setBrightness(brightValue);
}
void analog4(OSCMessage &msg) {                                                        // brillance totale de la plante
  ledState4 = msg.getInt(0);
  brightValue = map(ledState4, 254, 1024, 0, 255);
  ws2812fx.setBrightness(brightValue);
  ws2812fx_2.setBrightness(brightValue);
}

void analog5(OSCMessage &msg) {                                                        //speed control
  Serial.println("message!");
  
  ledState5 = msg.getInt(0);
  speedValue = map(ledState5, 274, 1024, 1200, 50);
  ws2812fx.setMode(FX_MODE_COMET);
  ws2812fx.setSpeed(speedValue);
  ws2812fx_2.setMode(FX_MODE_COMET);
  ws2812fx_2.setSpeed(speedValue); 
}
void analog6(OSCMessage &msg) {
// code here   
}
void analog7(OSCMessage &msg) {
  ledState7 = msg.getInt(0);
  colorValue = map(ledState7, 274, 1024, 4, 0);



  // do something different depending on the range value:
  switch (colorValue) {
    case 0:    // your hand is on the sensor
      setcolor = 0xFF2050;
      break;
    case 1:    // your hand is close to the sensor
      setcolor = 0xFF0050;
      break;
    case 2:    // your hand is a few inches from the sensor
      setcolor = 0x0000FF;
      break;
    case 3:    // your hand is nowhere near the sensor
      setcolor = 0x00FF00;
      break;
          case 4:    // your hand is on the sensor
      setcolor = 0xFFFFFF;
      break;
  }

  ws2812fx.setColor(setcolor);
  ws2812fx_2.setColor(setcolor);
}










void loop() {
  ws2812fx.service();
    ws2812fx_2.service();

  OSCMessage msg;
  int size = Udp.parsePacket();
    if (size > 0) {
    while (size--) {
      msg.fill(Udp.read());
    }
    if (!msg.hasError()) {
       
      msg.dispatch("/plantoid/100/95/analog/0", analog6);   // premier bouton ventricule droit / sparkel global
      msg.dispatch("/plantoid/100/95/analog/1", analog1);   // premier bouton ventricule gauche / effet pistils
      msg.dispatch("/plantoid/100/95/analog/2", analog2);
      msg.dispatch("/plantoid/100/95/analog/3", analog3);
      msg.dispatch("/plantoid/100/95/analog/4", analog4);   // second potar ventricule droit
      msg.dispatch("/plantoid/100/95/analog/5", analog5);   // premier potar, ventricule droit/speed control
      msg.dispatch("/plantoid/100/95/analog/6", analog0);
      msg.dispatch("/plantoid/100/95/analog/7", analog7);   // premier potard ventricule gauche / color control
      msg.empty();
    } else {
      error = msg.getError();
      Serial.print("error: ");
      Serial.println(error);
    }
  }
}
