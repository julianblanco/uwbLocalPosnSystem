
#include <SPI.h> 
#include "srcdwm1000/DW1000Ranging.h"
#include "srcdwm1000/DW1000Device.h"

#define RST 9
  

void setup() {
///
  Serial.begin(115200);
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
  Serial.print("from: "); Serial.println(DW1000Ranging.getDistantDevice()->getShortAddress(), HEX);  
 // Serial.print("\t Range: "); Serial.print(DW1000Ranging.getDistantDevice()->getRange()); Serial.print(" m"); 
  //Serial.print("\t RX power: "); Serial.print(DW1000Ranging.getDistantDevice()->getRXPower()); Serial.println(" dBm");
  
}

void DW1000RangingClass::initCommunication(unsigned int myRST, unsigned int mySS){
    // reset line to the chip
    _RST = myRST;
    _SS = mySS;
    _resetPeriod = DEFAULT_RESET_PERIOD;
    // reply times (same on both sides for symm. ranging)
    _replyDelayTimeUS = DEFAULT_REPLY_DELAY_TIME;
    //we set our timer delay
    _timerDelay = DEFAULT_TIMER_DELAY;
    
    
    DW1000.begin(0, myRST);
    DW1000.select(mySS);
}

void DW1000Class::begin(int irq, int rst) {
  // generous initial init/wake-up-idle delay
  delay(5);
  // start SPI
  SPI.begin(); 
  SPI.usingInterrupt(irq);
  // pin and basic member setup
  _rst = rst;
  _irq = irq;
  _deviceMode = IDLE_MODE;
  // attach interrupt
  attachInterrupt(_irq, DW1000Class::handleInterrupt, RISING);
  }

