import serial
import time

ser = serial.Serial('/dev/ttyACM0', 9600)  # replace 'COM3' with the name of your serial port

while True:
    message = input("Enter a message to send to Arduino: ")
    ser.write(message.encode('utf-8'))  # send the message to the Arduino
    time.sleep(0.1)  # wait for a short time to give the Arduino time to process the message

    if ser.in_waiting > 0:  # check if there is data waiting to be read from the Arduino
        response = ser.readline().decode('utf-8').rstrip()  # read the response and remove trailing newline character
        print(f"Received response from Arduino: {response}")
