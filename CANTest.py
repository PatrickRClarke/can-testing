# CANTest.py
# Patrick Clarke
# 3/17/2024


import can
import time

# Write a function for receiving a CAN message here.
def CANReceive():
    bus_receive = can.interface.Bus(channel='can0', bustype='socketcan')
    msg_in = bus_receive.recv(timeout=None)
    msg_id = int(msg_in.arbitration_id)
    return msg_id
    

# Initialize CAN Bus.
bus = can.interface.Bus(channel='can0', bustype='socketcan')
    

def main():

    # Start the test
    verifier = -1
    timeBegin = time.time()
    print("Starting tests ... ")
    
        
    # [1/4] PiBox sends a CAN Frame to the Propulsion Node
    timeOne = time.time()
    msg = can.Message(arbitration_id=1, data=[0,0,0,0,0,0,0,0], is_extended_id=False)
    bus.send(msg)
    print("[1/4] Testing: Pi Box -> Prop. Node -> Pi Box ...")

    while verifier != 2:
       verifier = CANReceive()
       
    timeTwo = time.time()
    result = timeTwo - timeOne
    print("Success: " + str(result))



    # [2/4] Pi Box sends a CAN frame to the Engine Node
    timeThree = time.time()
    msg = can.Message(arbitration_id=3, data=[0,0,0,0,0,0,0,0], is_extended_id=False)
    bus.send(msg)
    print("[2/4] Testing: Pi Box -> Engine Node -> Pi Box ...")

    while verifier != 4:
       verifier = CANReceive()

    timeFour = time.time()
    result = timeFour - timeThree
    print("Success: " + str(result))
    
       
    
    # [3/4] Pi Box sends a CAN frame to the Propulsion Node
    timeFive = time.time()
    msg = can.Message(arbitration_id=5, data=[0,0,0,0,0,0,0,0], is_extended_id=False)
    bus.send(msg)
    print("[3/4] Testing: Pi Box -> Propulsion Node -> Engine Node -> Pi Box ...")

    while verifier != 7:
       verifier = CANReceive()

    timeSix = time.time()
    result = timeSix - timeFive
    print("Success: " + str(result))



    # [4/4] Pi Box sends a CAN frame to the Engine Node
    timeSeven = time.time()
    msg = can.Message(arbitration_id=8, data=[0,0,0,0,0,0,0,0], is_extended_id=False)
    bus.send(msg)
    print("[4/4] Testing: Pi Box -> Engine Node -> Propulsion Node -> Pi Box  ...")

    while verifier != 10:
       verifier = CANReceive()

    timeEight = time.time()
    result = timeEight - timeSeven
    print("Success: " + str(result))


    # Finish the test
    timeFinal = time.time()
    result = timeFinal - timeBegin
    print("All tests completed in: " + str(result))
