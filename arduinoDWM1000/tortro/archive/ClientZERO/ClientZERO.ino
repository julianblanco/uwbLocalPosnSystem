#include <Arduino.h>
#include "srcdwm1000/spizero.h"
#include "srcdwm1000/DW1000Ranging.h"
#include "srcdwm1000/DW1000Device.h"

#define RST 9
  

void setup() {
///
  Serial1.begin(115200);
  delay(1000);
  //init the configuration
  DW1000Ranging.initCommunication(9, 10); //Reset and CS pin  
  //define the sketch as anchor. It will be great to dynamically change the type of module
  DW1000Ranging.attachNewRange(newRange);
  //we start the module as a tag
  DW1000Ranging.startAsTag("7D:00:22:EA:82:60:3B:9C", DW1000.MODE_LONGDATA_RANGE_ACCURACY);
}
void loop() { 
  DW1000Ranging.loop(); 
}

void newRange(){ 
  Serial1.print("from: "); Serial.print(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);  
  Serial1.print("\t Range: "); Serial.print(DW1000Ranging.getDistantDevice()->getRange()); Serial.print(" m"); 
  Serial1.print("\t RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");
  
}


