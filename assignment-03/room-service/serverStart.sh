#!/bin/bash
python3 mqttServer.py &
python3 httpServer.py &
python3 serialServer.py &
