import datetime
from config import *

class roomLogic:
    def __init__(self) -> None:
        self.prescence = '0'
        #self.brightness = '0'
        #self.lightState = 'off'
        #self.rollerBlinds = '0'
    
    def espNotify(self, prescence, brightness):
        self.prescence = prescence
       # self.brighness = brightness
        if(prescence == '0'):
            lightOff()
            if(isNight()):
                rollerBlindsDown()
        if(prescence == '1'):
            if(tooDark(brightness)):
                lightOn()
            if(isDay()):
                rollerBlindsUp()
    
    def automaticNotify(self):
        #this task should be checked periodically...No body will tell me 
        #when is night, unless i check the hour.
        if(isNight() and self.prescence == '0'):
            rollerBlindsDown()


        
