import datetime
from config import *

class roomLogic:
    def __init__(self) -> None:
        self.prescence = '0'
        #self.brightness = '0'
        #self.lightState = 'off'
        #self.rollerBlinds = '0'
    
    def espNotify(self, option, value):
        if option == 'presence':
            self.prescence = value
            if self.prescence == '0':
                lightOff()
                if(isNight()):
                    rollerBlindsDown()
            elif self.prescence == '1':
                if isDay():
                    rollerBlindsUp()

        if option == 'brightness':
            if tooDark(value):
                lightOn()
                
    
    def automaticNotify(self):
        #this task should be checked periodically...No body will tell me 
        #when is night, unless i check the hour.
        if(isNight() and self.prescence == '0'):
            rollerBlindsDown()


        
