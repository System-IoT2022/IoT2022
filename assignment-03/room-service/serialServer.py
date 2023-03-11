from config import *

if __name__ == '__main__':
    print("waiting for msg from serial line...")
    while True:
        msg = serialComm.listenToMsg()
        if msg == 'on':
            logger.write(getTimeLightStatePair('on'))
        if msg == 'off':
            logger.write(getTimeLightStatePair('off'))
        time.sleep(1)