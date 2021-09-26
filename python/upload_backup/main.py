import time
import serial
# from data import data


if __name__ == "__main__":
    midi_stomp = serial.Serial('/dev/cu.usbserial-110', 9600)
    print("connected... waiting")
    time.sleep(5)
    print("sending message...")
    midi_stomp.write(20)
    time.sleep(5)
    midi_stomp.write(30)
    time.sleep(1)
    midi_stomp.write(40)
    time.sleep(1)
    midi_stomp.write(50)
    time.sleep(1)
    midi_stomp.write(60)
    # midi_stomp.write(5)
    # midi_stomp.write(127)
