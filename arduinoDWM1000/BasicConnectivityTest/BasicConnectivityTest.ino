/*
 * Copyright (c) 2015 by Thomas Trojer <thomas@trojer.net>
 * Decawave DW1000 library for arduino.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @file BasicConnectivityTest.ino
 * Use this to test connectivity with your DW1000 from Arduino.
 * It performs an arbitrary setup of the chip and prints some information.
 */

#include <SPI.h>
#include "srcdwm1000/DW1000.h"

// connection pins
const uint8_t PIN_RST = 9; // reset pin
const uint8_t PIN_IRQ = 11; // irq pin
const uint8_t PIN_SS = 10; // spi select pin

void setup() {
  // DEBUG monitoring
   
  Serial1.begin(115200);
  // initialize the driver
  DW1000.begin(PIN_IRQ, PIN_RST);
  DW1000.select(PIN_SS);
  Serial1.println(("DW1000 initialized ..."));
  // general configuration
  DW1000.newConfiguration();
  DW1000.setDeviceAddress(7);
  DW1000.setNetworkId(12);
  DW1000.commitConfiguration();
  Serial1.println(F("Committed configuration ..."));
  // wait a bit
  delay(1000);
}

void loop() {
  // DEBUG chip info and registers pretty printed
  char msg[128];
  DW1000.getPrintableDeviceIdentifier(msg);
  Serial1.print("Device ID: "); Serial1.println(msg);
  DW1000.getPrintableExtendedUniqueIdentifier(msg);
  Serial1.print("Unique ID: "); Serial1.println(msg);
  DW1000.getPrintableNetworkIdAndShortAddress(msg);
  Serial1.print("Network ID & Device Address: "); Serial1.println(msg);
  DW1000.getPrintableDeviceMode(msg);
  Serial1.print("Device mode: "); Serial1.println(msg);
  // wait a bit
  delay(10000);
}
