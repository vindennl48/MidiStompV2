import time
import serial
# from data import data

com = serial.Serial('/dev/cu.usbserial-10', 9600, timeout=60)

def to_bte(num, size=1):
    value = (num).to_bytes(size, 'big')
    print(f"    > to_bte({value}, {num})")
    return value
def from_bte(num):
    value = int.from_bytes(num, 'big')
    print(f"    > from_bte({num}, {value})")
    return value
def com_read():
    return from_bte( com.read() )
def com_write(num):
    com.write( to_bte(num) )

def serial_connect():
    print("----> Connecting..")
    com_write(0xff)
    if com_read() == 0xff:
        print("      Connected!")
        return True
    raise Exception(f"ERROR>Connection Failed")
    return False

def serial_disconnect():
    print("----> Disconnecting..")
    com_write(0)
    if com_read() == 0xff:
        print("     Disconnected!")
        return True
    raise Exception("ERROR>Disconnect Failed")
    return False

MODE_READ_UINT8_T   = 1
MODE_READ_UINT16_T  = 2
MODE_READ_TEXT      = 3
MODE_READ_BLOCK     = 4
MODE_WRITE_UINT8_T  = 5
MODE_WRITE_UINT16_T = 6
MODE_WRITE_TEXT     = 7
MODE_WRITE_BLOCK    = 8
def serial_mode(mode):
    print("      Setting serial mode..")
    com_write(mode)
    if com_read() == 0xff:
        print(f"      Serial mode set! ({mode})")
        return True
    raise Exception(f"ERROR>serial_mode({mode}) - failed")
    return False

def read_uint8_t(uint16_t):
    print(f"----> Reading UINT8_T at addr ({uint16_t})..")
    serial_mode(MODE_READ_UINT8_T)
    com_write( uint16_t >> 8 )
    com_write( uint16_t & 0xff )
    value = com_read()
    if com_read() == 0xff:
        return value
    raise Exception(f"ERROR>read_uint8_t({uint16_t}) - failed")
    return False

def read_uint16_t(uint16_t):
    print(f"----> Reading UINT16_T at addr ({uint16_t})..")
    serial_mode(MODE_READ_UINT16_T)
    com_write( uint16_t >> 8 )
    com_write( uint16_t & 0xff )
    value = com_read() << 8 | com_read()
    if com_read() == 0xff:
        return value
    raise Exception(f"ERROR>read_uint8_t({uint16_t}) - failed")
    return False

def read_block(uint16_t, sz=64):
    serial_mode(MODE_READ_BLOCK)
    com_write( uint16_t >> 8 )
    com_write( uint16_t & 0xff )
    com_write( sz >> 8 )
    com_write( sz & 0xff )

    value = com.read(sz)

    if com_read() == 0xff:
        return value
    raise Exception(f"ERROR>read_uint8_t({uint16_t}) - failed")
    return False


if __name__ == "__main__":
    print("----> Loading..")
    time.sleep(5)
    print("      Complete!")

    serial_connect()

    #value = read_block(0, 3200)
    #print(value)
    # for v in value:
        # print(v, end=", ")

    # print(f"read_uint8_t({i}): {value}, {to_bte(value)}")

#    with open('backup.ms2', 'wb') as f:
#        for i in range(20):
#            value = read_block(i*3200, 3200)
#            print(f"read_block({i}): {value}")
#            f.write( value )

    with open('backup.ms2', 'wb') as f:
        for i in range(4):
            value = read_block(i*16000, 16000)
            print(f"read_block({i}): {value}")
            f.write( value )
