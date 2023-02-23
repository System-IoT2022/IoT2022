import serial
import time
import datetime


class SerialCommunication:
    def __init__(self, _portName='/dev/ttyACM0', _timeout=0):
        self.arduino = serial.Serial(port = _portName, timeout = _timeout)
        self.arduino = serial.Serial(port = _portName, timeout=0)
        time.sleep(2)


    def sendMsg(self, msg):
        print("forwarded to arduino : {}".format(msg))
        self.arduino.write(str.encode(msg))
