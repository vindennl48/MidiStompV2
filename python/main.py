import COM
import Debug
import eeprom_map as emap

# Debug.will_print = True

if __name__ == "__main__":
    COM.initialize()
    block = COM.read_block(0, 512)
    print(block)
