import serial
import time
'''
import serial.tools.list_ports
ports = list(serial.tools.list_ports.comports())
for p in ports:
    if "ACM" in p.description:
        serialPort = p
    
'''

class SerialCommunication:
    def __init__(self, _portName='/dev/ttyACM0', _timeout=0):
        self.arduino = serial.Serial(port = _portName, timeout = _timeout)
        self.arduino = serial.Serial(port = _portName, timeout=0)
        time.sleep(2)


    def sendMsg(self, option):
        if(option == '1'):
            self.arduino.write(str.encode('1'))
            print("LED turned on")
            time.sleep(1)

        if(option == '0'):
            self.arduino.write(str.encode('0'))
            print("LED turned off")
