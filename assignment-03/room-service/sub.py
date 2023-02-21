# python 3.8
import json
import random
import time

from paho.mqtt import client as mqtt_client


BROKER = 'ga1dae9f.ala.us-east-1.emqxsl.com'
PORT = 8084
TOPIC = "provapc"
# generate client ID with pub prefix randomly
CLIENT_ID = "provapc2"
USERNAME = 'iot'
PASSWORD = 'iot'
FLAG_CONNECTED = 0

def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
        client.subscribe(TOPIC)
    else:
        print("Failed to connect, return code {rc}".format(rc=rc), )


def on_message(client, userdata, msg):
    print("Received `{payload}` from `{topic}` topic".format(
        payload=msg.payload.decode(), topic=msg.topic))


def connect_mqtt():
    client = mqtt_client.Client(CLIENT_ID, transport='websockets')
    client.tls_set(ca_certs='emqxsl-ca.crt')
    client.username_pw_set(USERNAME, PASSWORD)
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect(BROKER, PORT)
    return client


def run():
    client = connect_mqtt()
    client.loop_forever()


if __name__ == '__main__':
    run()