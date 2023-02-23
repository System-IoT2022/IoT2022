#!/usr/bin/python           # This is server.py file

import socket               # Import socket module
import datetime
import json

s = socket.socket()         # Create a socket object
host = socket.gethostname() # Get local machine name
port = 12346         # Reserve a port for your service.
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind((host, port))        # Bind to the port

s.listen(5)                 # Now wait for client connection.

# output = 'Thank you for connecting'
date = '2021-05-21 11:22:03'
datem = datetime.datetime.strptime(date, "%Y-%m-%d %H:%M:%S")
date1 = '2021-05-21 13:22:03'
daten  = datetime.datetime.strptime(date1, "%Y-%m-%d %H:%M:%S")
date = f'{daten.hour}:{daten.minute}:{daten.second}'
date1  = f'{datem.hour}:{datem.minute}:{datem.second}'
output = [{date : 'on'}, {date1 : 'off'}]
data = json.dumps(output)

def run():
   c, addr = s.accept()     # Establish connection with client.
   c.sendall(bytes(data, encoding="utf-8"))
   c.close()                # Close the connection

if __name__ == '__main__':
    while True:
      run()