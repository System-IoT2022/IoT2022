#include "Arduino.h"
#include "MsgServiceBT.h"

MsgServiceBT msgServiceBT(BT_RX_PIN,BT_TX_PIN);

MsgServiceBT::MsgServiceBT(int rxPin, int txPin){
  channel = new SoftwareSerial(rxPin, txPin);
}

void MsgServiceBT::init(){
  content.reserve(256);
  channel->begin(9600);
  availableMsg = NULL;
}

bool MsgServiceBT::sendMsg(const String& msg){
  Serial.println(msg);  
}

bool MsgServiceBT::isMsgAvailable(){
  while (channel->available()) {
    char ch = (char) channel->read();
    if (ch == '\n'){
      availableMsg = new Msg(content); 
      content = "";
      return true;    
    } else {
      content += ch;      
    }
  }
  return false;  
}

Msg* MsgServiceBT::receiveMsg(){
  if (availableMsg != NULL){
    Msg* msg = availableMsg;
    availableMsg = NULL;
    return msg;  
  } else {
    return NULL;
  }
}
