import serial
import time


class SerialCommunication:
    def __init__(self, _portName='/dev/ttyACM0', _timeout=0):
        self.arduino = serial.Serial(port = _portName, timeout = _timeout)
        time.sleep(2)


    def sendMsg(self, msg):
        print("forwarded to arduino : {}".format(msg))
        self.arduino.write(str.encode(msg))
        time.sleep(1)

    def listenToMsg(self):
        print("waiting for msg from serial line...")
        line = self.arduino.readline().decode().rstrip()
        return line
            
                


