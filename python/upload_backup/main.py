import time
import serial
# from data import data


if __name__ == "__main__":
    midi_stomp = serial.Serial('/dev/cu.usbserial-110', 9600)
    print("connected... waiting")
    time.sleep(5)
    print("sending message...")
    midi_stomp.write(20)
