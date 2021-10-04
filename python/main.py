import COM
import Debug
import eeprom_map as emap
from GetArgs import getargs

if __name__ == "__main__":
    myargs = getargs([
        '--backup', 'filename',
        '-u', '--upload',
        '-v', '--verbose',
        '--test',
    ])
    args   = myargs.getargs()

    if '-v' in args or '--verbose' in args:
        Debug.will_print = True

    if '--backup' in args:
        COM.initialize()
        filename = args['filename'].split('.')[0]

        with open(f"{filename}.ms2", "wb") as f:
            for i in range(4):
                print(f" - Saving.. {int(((i*16000)/64000)*100)}%", end="\r", flush=True)
                f.write(COM.read_block(i*16000, 16000))

        print("Saving Complete!")

    if '--test' in args:
        COM.initialize()
