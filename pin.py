from random import randint
from typing import List
import threading
import time

pins: List[str] = [] # should use redis instead

def generate_pin(length: int = 4) -> None:
    pins.append(''.join(str(randint(0,9)) for _ in range(length)))

def remove_thread():
    while True:
        if pins: # validate the existence of a pin
            pins.pop(-1) # reverse iterate
            time.sleep(30) # sleep for 30s

def launch_threads() -> None:
    try:
        pin_remove = threading.Thread(target=remove_thread).start()
    except Exception as err:
        print(f"error: {err}")