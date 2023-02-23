#ifndef __MSGSERVICEBT__
#define __MSGSERVICEBT__

#include "Config.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
#include "MsgService.h"
class MsgServiceBT {
    
public: 
  MsgServiceBT(int rxPin, int txPin);  
  void init();  
  bool isMsgAvailable();
  Msg* receiveMsg();
  bool sendMsg(const String& msg);

private:
  String content;
  Msg* availableMsg;
  SoftwareSerial* channel;
  
};
extern MsgServiceBT msgServiceBT;
#endif
