from serialComm import *
from serverLogger import *

TURN_OFF_LIGHT = 'light:0'
TURN_ON_LIGHT = 'light:1'
ROLLER_BLINDS_UP = 'servo:180'
ROLLER_BLINDS_DOWN = 'servo:0'
BRIGHTNESS_THRESHOLD = 10
MORNING = 8
EVENING = 19

serialComm = SerialCommunication('/dev/ttyUSB0') #put the port
logger = ServerLogger('light.txt')

def setRollerBlindsWithDegree(degree):
    return f'servo:{degree}'

def getDateHourMinuteSecondNow():
   now = datetime.datetime.now()
   daten = datetime.datetime.strptime(str(now), "%Y-%m-%d %H:%M:%S")
   return f'{daten.hour}:{daten.minute}:{daten.second}'

# the lightState can be 'on' or 'off'
def getTimeLightStatePair(lightState):
    key = getDateHourMinuteSecondNow()
    return f'{key}:{lightState}'


def lightOn():
    serialComm.sendMsg(TURN_ON_LIGHT)
    logger.write(getTimeLightStatePair('on'))

def lightOff():
    serialComm.sendMsg(TURN_OFF_LIGHT)
    logger.write(getTimeLightStatePair('off'))

def rollerBlindsUp():
    serialComm.sendMsg(ROLLER_BLINDS_UP)

def rollerBlindsDown():
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
