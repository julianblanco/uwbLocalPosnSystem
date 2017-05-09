#include <SPI.h> 


#include "srcdwm1000/DW1000Ranging.h"
#include "srcdwm1000/DW1000Device.h"

#define RST  9

void setup() {
   CLKPR = (1 << CLKPCE);
  CLKPR = 0x01;
  Serial.begin(115200);
  delay(1000);
  //init the configuration
  DW1000Ranging.initCommunication(9, 10); //Reset and CS pin  
  //define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  //we start the module as an anchor 
  DW1000Ranging.startAsAnchor("32:17:5B:D5:A9:9A:E2:44", DW1000.MODE_LONGDATA_FAST_ACCURACY); 
}


void loop() { 
  DW1000Ranging.loop(); 
}

void newRange(){  
  Serial.print("from: "); Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);
  Serial.print("\t Range: "); Serial.print(DW1000Ranging.getDistantDevice()->getRange()); Serial.print(" m"); 
  Serial.print("\t RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");
  
}


