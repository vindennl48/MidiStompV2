import COM
import Debug
import eeprom_map as     emap
from   GetArgs    import getargs
from   Upload     import Data

if __name__ == "__main__":
    myargs = getargs([
        '--backup', 'filename',
        '-u', '--upload',
        '-v', '--verbose',
        '--test',
        '--show', 'addr', 'size',
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

    if '--show' in args:
        COM.initialize()
        print(COM.read_block(int(args['addr']), int(args['size'])))

    elif '--test' in args:
        # COM.initialize()
        if "Colors" in Data:
            for color in Data["Colors"]:
                if "id" not in color:
                    raise Exception("'id' property is needed in colors!")
                addr = int(color["id"]) * emap.COLOR_SZ
                if "name" in color:
                    # COM.write_block(
                        # addr,
                        # COM.text_fix( color["name"] )
                    # )
                    print(f"addr: {addr}")
                    print(f"text: {COM.text_fix( color['name'] )}")
                if "channels" in color:
                    # COM.write_block(
                        # addr + 13,
                        # bytes( color["channels"] )
                    # )
                    print(f"addr: {addr+13}")
                    print(f"text: {bytes( color['channels'] )}")
