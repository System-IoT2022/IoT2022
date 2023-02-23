import datetime
from serialComm import *

TURN_OFF_LIGHT = 'light:0'
TURN_ON_LIGHT = 'light:1'
ROLLER_BLINDS_UP = 'servo:180'
ROLLER_BLINDS_DOWN = 'servo:0'
BRIGHTNESS_THRESHOLD = 10
MORNING = 8
EVENING = 19

serialComm = SerialCommunication('/dev/ttyUSB0') #put the port

class roomLogic:
    def __init__(self) -> None:
        self.prescence = 0
        self.brightness = 0
    def lightOn(self):
        serialComm.sendMsg(TURN_ON_LIGHT)
    def lightOff(self):
        serialComm.sendMsg(TURN_OFF_LIGHT)
    def rollerBlindsUp(self):
        serialComm.sendMsg(ROLLER_BLINDS_UP)
    def rollerBlindsDown(self):
        serialComm.sendMsg(ROLLER_BLINDS_DOWN)
    def tooDark(self, brightness):
        return float(brightness) < BRIGHTNESS_THRESHOLD
    def isDay(self):
        now = datetime.datetime.now()
        today8am = now.replace(hour=MORNING, minute=0, second=0, microsecond=0)
        today7pm = now.replace(hour=EVENING, minute=0, second=0, microsecond=0)
        return now > today8am and now < today7pm
    
    def isNight(self):
        now = datetime.datetime.now()
        today8am = now.replace(hour=MORNING, minute=0, second=0, microsecond=0)
        today7pm = now.replace(hour=EVENING, minute=0, second=0, microsecond=0)
        return now > today7pm or now < today8am

    def espNotify(self, prescence, brightness):
        self.prescence = prescence
        self.brighness = brightness
        if(prescence == '0'):
            self.lightOff()
            if(self.isNight()):
                self.rollerBlindsDown()
        if(prescence == '1'):
            if(self.tooDark(brightness)):
                self.lightOn()
            if(self.isDay()):
                self.rollerBlindsUp()
    
    def automaticNotify(self):
        #this task should be checked periodically...No body will tell me 
        #when is night, unless i check the hour.
        if(self.isNight() and self.prescence == '0'):
            self.rollerBlindsDown()


        
