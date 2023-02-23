#!/usr/bin/python           # This is server.py file

import socket               # Import socket module
import datetime
import json
import time
from serverLogger import *

s = socket.socket()         # Create a socket object
host = socket.gethostname() # Get local machine name
port = 12345         # Reserve a port for your service.
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((host, port))        # Bind to the port

s.listen(5)                 # Now wait for client connection.

# output = 'Thank you for connecting'
logger = ServerLogger('light.txt')

def getDateHourMinuteSecondNow():
   now = datetime.datetime.now(  )
   daten = datetime.datetime.strptime(str(now), "%Y-%m-%d %H:%M:%S.%f")
   return f'{daten.hour}:{daten.minute}:{daten.second}'

# the lightState can be 'on' or 'off'
def getTimeLightStatePair(lightState):
    key = getDateHourMinuteSecondNow()
    return {key : lightState}

def getData():
   lines = logger.read()
   return json.dumps(lines)

def run():
   c, addr = s.accept()     # Establish connection with client.
   print(c.recv(1024))
   c.sendall(bytes(getData(), encoding="utf-8"))
   c.close()                # Close the connection

if __name__ == '__main__':
    while True:
      #logger.write(getTimeLightStatePair('on'))
      #a = logger.write('on')
      #print(a)
      run()
      time.sleep(1)
      