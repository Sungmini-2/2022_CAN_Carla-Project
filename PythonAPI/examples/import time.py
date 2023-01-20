import time
import can
import cantools
from ECB import *
bus= can.interface.Bus(bustype='socketcan', channel='can0', bitrate=250000)
db = cantools.db.load_file('/home/jo/tmp/PythonAPI/examples/DBC/honda.dbc')

while 1 :
    message = bus.recv()
    message.data = ecb.dec(message.data)
    
    
    if 330 < message.arbitration_id <351:
        message.arbitration_id = 330
        
    elif 419 <message.arbitration_id < 441:
        message.arbitration_id = 419
    
    elif 441 <message.arbitration_id < 464:
        message.arbitration_id = 441
    
    elif 464 < message.arbitration_id < 485:
        message.arbitration_id = 464
        
    elif 485 < message.arbitration_id < 506 :
         message.arbitration_id=485 
         
    elif 505 < message.arbitration_id < 527 :
         message.arbitration_id=485
         
    print(db.decode_message(message.arbitration_id, message.data))
