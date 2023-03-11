import time
from roomLogic import roomLogic

roomController = roomLogic()

if __name__ == '__main__':
    print('periodic check')
    while True:
        roomController.automaticNotify()
        time.sleep(1)