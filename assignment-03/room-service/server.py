#!/usr/bin/python           # This is server.py file

import socket               # Import socket module
import datetime
import json

s = socket.socket()         # Create a socket object
host = socket.gethostname() # Get local machine name
port = 12346             # Reserve a port for your service.
s.bind((host, port))        # Bind to the port

s.listen(5)                 # Now wait for client connection.

# output = 'Thank you for connecting'
date = '2021-05-21 11:22:03'
datem = datetime.datetime.strptime(date, "%Y-%m-%d %H:%M:%S")
output = {"dataHour" : datem.hour, "pir" : 1, "brightness" : 250}
data = json.dumps(output)

while True:
   c, addr = s.accept()     # Establish connection with client.
   c.sendall(bytes(data, encoding="utf-8"))
   c.close()                # Close the connection