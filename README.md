# pin-system
basic pin system for stuff

# api structure
#### endpoints:
#### *GET* `api/pin`
generate a pin (30 second timeout)

#### *GET* `api/pins`
view currently generated pins
  - response:
    - body:
      - type: json
      - content:
      ```buildoutcfg
      {
        "pins": []
      }
      ```
#### *POST* `api/pin{pin}`
check pin against valid pins
  - request:
    - content:
    ```buildoutcfg
    {
      "pin":
    }
    ```
  - response:
    - body:
      - type: json
      - content: 
        `{"valid_pin"}`
    
