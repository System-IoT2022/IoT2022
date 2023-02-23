import socket
import time

PORT = 12345

def send_message(host, port, message):
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        s.sendall(message.encode())
        print(f"Sent message: {message}")
        print(s.recv(1024))

# 0 show lighting history
# 1 [0-1] light on/off
# 2 [degree]  roller blind degree
if __name__ == "__main__":
    while True:
        msg = '0'
        send_message(socket.gethostname(), PORT, msg)
        time.sleep(1)
        