import time
import serial
# from data import data


if __name__ == "__main__":
    midi_stomp = serial.Serial('/dev/cu.usbserial-10', 9600)
    print("connected... waiting")
    time.sleep(5)
    print("sending message...")

    midi_stomp.write((0xff).to_bytes(1,'big'))
    if midi_stomp.read(1) != 0xFF:
        midi_stomp.write((1).to_bytes(1,'big'))
        if midi_stomp.read(1) != 0xFF:
            midi_stomp.write((0).to_bytes(1,'big'))
            midi_stomp.write((0).to_bytes(1,'big'))
            print( f"result -> {midi_stomp.read(1)}" )

            midi_stomp.write((0).to_bytes(1,'big'))  ## exit
            midi_stomp.write((0).to_bytes(1,'big'))  ## exit

# import time
# import serial
# # from data import data
# 
# E_INIT         = 1
# E_WRITE_UINT8  = 2
# E_WRITE_UINT16 = 3
# E_WRITE_TEXT   = 4
# 
# def serial_connect():
#     midi_stomp.write((E_INIT).to_bytes(1,'big'))
#     return midi_stomp.read(1)
# 
# def serial_write_uint8_t(uint8_t):
#     midi_stomp.write((E_WRITE_UINT8).to_bytes(1,'big'))
#     midi_stomp.write(uint8_t.to_bytes(1,'big'))
#     return midi_stomp.read(1)
# 
# def serial_write_uint16_t(uint16_t):
#     midi_stomp.write((E_WRITE_UINT16).to_bytes(1,'big'))
#     midi_stomp.write(uint16_t.to_bytes(2,'big'))
# 
#     print(uint16_t)
#     print()
# 
#     return midi_stomp.read(1)
# 
# def serial_write_text(text):
#     midi_stomp.write((E_WRITE_TEXT).to_bytes(1,'big'))
#     midi_stomp.write(text.encode('utf-8'))
#     return midi_stomp.read(1)
# 
# if __name__ == "__main__":
#     midi_stomp = serial.Serial('/dev/cu.usbserial-10', 9600)
#     time.sleep(5)
#     print("initializing connection..")
# 
#     if (serial_connect()):
#         print("Connected!")
# 
#     print("sending message...")
#     if (serial_write_uint16_t(1127)):
#         print("Message complete!")
