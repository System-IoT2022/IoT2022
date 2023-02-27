import serial
import time


class SerialCommunication:
    def __init__(self, _portName, _baudrate=9600, _timeout=5):
        self.arduino = serial.Serial(port = _portName, baudrate=_baudrate, timeout = _timeout)
        time.sleep(2)


    def sendMsg(self, msg):
        print("forwarded to arduino : {}".format(msg))
        msg += '\n'
        self.arduino.write(str.encode(msg, 'utf-8'))
        #self.arduino.write(bytes(msg, 'utf-8'))
        time.sleep(1)

    def listenToMsg(self):
        print("waiting for msg from serial line...")
        line = self.arduino.readline().decode().rstrip()
        return line
            
                


