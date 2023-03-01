import socket
import time

PORT = 12345
class MsgClient:
    def __init__(self, port, hostName) -> None:
        self.port = port
        self.hostName = hostName

    def send_message(self, message):
        with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
            s.connect((self.hostName, self.port))
            s.sendall(message.encode())
            print(f"Sent message: {message}")
            receivedMsg = s.recv(1024).decode()
            print(f"Received message : {receivedMsg}\n")
            return receivedMsg

msgClient = MsgClient(PORT, socket.gethostname())
# 0 show lighting history
# 1 [0-1] light on/off
# 2 [degree]  roller blind degree
if __name__ == "__main__":
    while True:
        msg = input("# 0 show lighting history \n 1 [0-1] light on/off \n[degree]  roller blind degree\n")
        msgClient.send_message(msg)
        time.sleep(1)
        