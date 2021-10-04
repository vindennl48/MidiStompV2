import serial.tools.list_ports as ports
import time
import serial
import Debug

com = ""

MODE_READ_UINT8_T   = 1
MODE_READ_UINT16_T  = 2
MODE_READ_TEXT      = 3
MODE_READ_BLOCK     = 4
MODE_WRITE_UINT8_T  = 5
MODE_WRITE_UINT16_T = 6
MODE_WRITE_TEXT     = 7
MODE_WRITE_BLOCK    = 8

def initialize(baudrate=9600):
    global com
    Debug.Print_nline("Loading..")

    com_ports = list(ports.comports()) # create a list of com ['COM1','COM2'] 
    com_port  = ""

    for i in com_ports:
        if "usbserial" in i.device:
            com_port = i.device

    com = serial.Serial(com_port, baudrate, timeout=60)
    time.sleep(5)
    serial_connect()
    Debug.Print_nline("Complete!", 2)

def serial_connect():
    Debug.Print_nline("Connecting..")
    write(0xff)
    if read() == 0xff:
        Debug.Print_nline("Connected!", 2)
        return True
    raise Exception(f"ERROR>Connection Failed")
    return False

def serial_mode(mode):
    Debug.Print_nline("Setting serial mode..", 2)
    write(mode)
    if read() == 0xff:
        Debug.Print_nline(f"Serial mode set! ({mode})", 2)
        return True
    raise Exception(f"ERROR>serial_mode({mode}) - failed")
    return False

def to_bte(data, size=1):
    value = (data).to_bytes(size, 'big')
    Debug.Print_nline(f"to_bte({value}, {data})", 4)
    return value

def to_num(byte):
    data = int.from_bytes(byte, 'big')
    Debug.Print_nline(f"to_num({byte}, {data})", 4)
    return data

def to_str(byte):
    data = byte.decode()
    Debug.Print_nline(f"to_str({byte}, {data})", 4)
    return data

def read():
    return to_num(com.read())

def write(data):
    com.write( to_bte(data) )

def text_fix(text, encode=True):
    result = (text.upper().ljust(12)[0:12]+'\0')
    if encode:
        return result.encode('utf-8')
    else:
        return result

def read_block(addr, size=64):
    ## Returns as byte array
    serial_mode(MODE_READ_BLOCK)
    write( addr >> 8 )
    write( addr & 0xff )
    write( size >> 8 )
    write( size & 0xff )

    block = com.read(size)

    if read() == 0xff:
        return block
    raise Exception(f"ERROR>read_block({addr}) - failed")

def write_block(addr, block):
    ## block MUST be byte array
    serial_mode(MODE_WRITE_BLOCK)
    write( addr >> 8 )
    write( addr & 0xff )
    write( size >> 8 )
    write( size & 0xff )

    com.write(block)

    if read() == 0xff:
        return True
    raise Exception(f"ERROR>read_block({addr}) - failed")
