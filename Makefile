ARDUINO_LIBS  = LiquidCrystal_I2C Wire MIDI_Library #Rotary
ARDUINO_DIR   = /Applications/Arduino.app/Contents/Java
MONITOR_PORT  = /dev/cu.usbserial*
ARDMK_VENDOR  = arduino
BOARD_TAG     = nano
BOARD_SUB     = atmega328
include /usr/local/opt/arduino-mk/Arduino.mk
