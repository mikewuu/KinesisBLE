#include <Arduino.h>
#include <SPI.h> 
#include "MCP23S17.h"

MCP outputchip(0, 29); 


#define MCP_PIN 1       // MCP pin 1-16

void setup() {
  
    pinMode(LED_BUILTIN, OUTPUT);
  // put your setup code here, to run once:

  outputchip.begin();

  outputchip.pinMode(MCP_PIN, OUTPUT);    // Set pin 1 as output
  

}

void loop() {

  outputchip.digitalWrite(MCP_PIN, HIGH);   
  digitalWrite(LED_BUILTIN, HIGH); 
  delay(500);

  outputchip.digitalWrite(MCP_PIN, LOW);   
  digitalWrite(LED_BUILTIN, LOW);
  delay(500);
  
}
