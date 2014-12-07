#include <SPI.h>
#include <boards.h>
#include <ble_shield.h>
#include <services.h>
#include "Boards.h"

#define LED_PIN    6

void setup()
{
  SPI.setDataMode(SPI_MODE0);
  SPI.setBitOrder(LSBFIRST);
  SPI.setClockDivider(SPI_CLOCK_DIV16);
  SPI.begin();

  ble_begin();
  
  pinMode(LED_PIN, OUTPUT);
  
}

void loop()
{
  static boolean analog_enabled = false;
  static byte old_state = LOW;
  
  // If data is ready
  while(ble_available())
  {
    // read out command and data
    byte data0 = ble_read();
    
    if (data0 == 0x03)  // Command is to control digital out pin
    {
        digitalWrite(LED_PIN, HIGH);
    }
    else if (data0 == 0x04) // Command is to enable analog in reading
    {
        digitalWrite(LED_PIN, LOW);
    }
  }
  
  
  if (!ble_connected())
  {
    analog_enabled = false;
    digitalWrite(LED_PIN, LOW);
  }
  
  // Allow BLE Shield to send/receive data
  ble_do_events();  
}



