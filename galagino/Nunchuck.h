/*
 * Needs MCP23017 Library installed, either via Library Manager or https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library
 * This was mostly written by AI but does work!
 */

#ifndef _NUNCHUCK_H_
#define _NUNCHUCK_H_

#include <Wire.h>
#include <Adafruit_MCP23X17.h>

#define BUTTON_LEFT   (1 << 0)
#define BUTTON_RIGHT  (1 << 1)
#define BUTTON_UP     (1 << 2)
#define BUTTON_DOWN   (1 << 3)
#define BUTTON_FIRE   (1 << 4)
#define BUTTON_EXTRA  (1 << 5)
#define BUTTON_COIN   (1 << 6)
#define BUTTON_START  (1 << 7)

// I2C Pin Definitions
#define NUNCHUCK_SDA 22
#define NUNCHUCK_SCL 27
#define MCP23017_ADDRESS 0x20

// MCP23017 Pin Assignments
#define MCP_LEFT_PIN   0  // GPA0 = LEFT (pin 21)
#define MCP_RIGHT_PIN  1  // GPA1 = RIGHT (pin 22)
#define MCP_UP_PIN     2  // GPA2 = UP (pin 23)
#define MCP_DOWN_PIN   3  // GPA3 = DOWN (pin 24)
#define MCP_FIRE_PIN   4  // GPA4 = FIRE (pin 25)
#define MCP_EXTRA_PIN  5  // GPA5 = EXTRA (pin 26)
#define MCP_COIN_PIN   6  // GPA6 = COIN (pin 27)
#define MCP_START_PIN  7  // GPA7 = START (pin 28)

Adafruit_MCP23X17 mcp;

void nunchuckSetup() {
  Wire.begin(NUNCHUCK_SDA, NUNCHUCK_SCL);
  
  if (!mcp.begin_I2C(MCP23017_ADDRESS, &Wire)) {
    Serial.println("MCP23017 not detected!");
    delay(1000);
    return;
  }

  // Configure all button pins with pullups
  mcp.pinMode(MCP_LEFT_PIN, INPUT_PULLUP);
  mcp.pinMode(MCP_RIGHT_PIN, INPUT_PULLUP);
  mcp.pinMode(MCP_UP_PIN, INPUT_PULLUP);
  mcp.pinMode(MCP_DOWN_PIN, INPUT_PULLUP);
  mcp.pinMode(MCP_FIRE_PIN, INPUT_PULLUP);
  mcp.pinMode(MCP_EXTRA_PIN, INPUT_PULLUP);
  mcp.pinMode(MCP_COIN_PIN, INPUT_PULLUP);
  mcp.pinMode(MCP_START_PIN, INPUT_PULLUP);

  Serial.println("MCP23017 i2c initialized");
}

unsigned char getNunchuckInput() {
  // Read all buttons at once (active LOW due to pullups)
  uint8_t buttonStates = mcp.readGPIOA();
  
  // Return bitmask with correct logical mapping
  return ((!(buttonStates & (1 << MCP_UP_PIN)))    ? BUTTON_UP    : 0) |
         ((!(buttonStates & (1 << MCP_DOWN_PIN)))  ? BUTTON_DOWN  : 0) |
         ((!(buttonStates & (1 << MCP_LEFT_PIN)))  ? BUTTON_LEFT  : 0) |
         ((!(buttonStates & (1 << MCP_RIGHT_PIN))) ? BUTTON_RIGHT : 0) |
         ((!(buttonStates & (1 << MCP_FIRE_PIN)))  ? BUTTON_FIRE  : 0) |
         ((!(buttonStates & (1 << MCP_EXTRA_PIN))) ? BUTTON_EXTRA : 0) |
         ((!(buttonStates & (1 << MCP_COIN_PIN)))  ? BUTTON_COIN  : 0) |
         ((!(buttonStates & (1 << MCP_START_PIN))) ? BUTTON_START : 0);
}

#endif // _NUNCHUCK_H_
