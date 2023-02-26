# python 3.8
import json
import random
import time

from paho.mqtt import client as mqtt_client
from roomLogic import roomLogic


BROKER = 'broker.hivemq.com'
PORT = 1883
TOPIC = "iot-server-esp-32149259214"
CLIENT_ID = ""
FLAG_CONNECTED = 0

roomController = roomLogic()

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
        client.subscribe(TOPIC)
    else:
        print("Failed to connect, return code {rc}".format(rc=rc), )

def on_message(client, userdata, msg):
    print("Received `{payload}` from `{topic}` topic".format(
        payload=msg.payload.decode(), topic=msg.topic))
    
    messageStr = msg.payload.decode().split(" ")
    #serialComm.sendMsg(messageStr.split(" "))
    roomController.espNotify(option=messageStr[0], value=messageStr[1])


def connect_mqtt():
    client = mqtt_client.Client(CLIENT_ID, transport='tcp')
    # client.tls_set(ca_certs='emqxsl-ca.crt')
    # client.username_pw_set(USERNAME, PASSWORD)
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(BROKER, PORT)
    return client


if __name__ == '__main__':
    client = connect_mqtt()
    client.loop_forever()
    while True:
        roomController.automaticNotify()
        print('periodic check')
        time.sleep(60)
    