import fastapi
import uvicorn
from pin import *

api = fastapi.FastAPI()

@api.get("/api/pin")
def create_pin():
    generate_pin(4)

@api.get("/api/pins")
def view_pins():
    return pins

@api.post("/api/pin/{pin}")
def check_pin(pin: str):
    if pin in pins:
        return{"valid_pin"}

launch_threads()

if __name__ == "__main__":
    uvicorn.run(api)