from threading import Lock

class ServerLogger:
    def __init__(self, filename) -> None:
        self.fileName = filename
        self.thread_lock = Lock()

    def write(self, msg):
        self.thread_lock.acquire()
        with open(self.fileName, "a") as file_object:
            file_object.write(msg)
        self.thread_lock.release()


    def read(self):
        self.thread_lock.acquire()
        with open(self.fileName, "r") as file_object:
            lines = file_object.readlines()
        self.thread_lock.release()
        return lines



