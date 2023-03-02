from threading import Lock
import json
import os

class ServerLogger:
    def __init__(self, filename) -> None:
        self.fileName = filename
        self.thread_lock = Lock()

    def write(self, msg):
        data = self.read()
        #print(data)
        data.append(msg)
        self.thread_lock.acquire()
        with open(self.fileName, "w") as file_object:
            json.dump(data, file_object, indent=4, separators=(',', ' '))
            
        self.thread_lock.release()


    def read(self):
        self.thread_lock.acquire()
        data = []
        if os.path.exists(self.fileName) and os.stat(self.fileName).st_size > 0:
            with open(self.fileName, "r") as file_object:
                data = json.load(file_object)

        self.thread_lock.release()
        return data



