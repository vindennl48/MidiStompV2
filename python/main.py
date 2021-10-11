import COM
import Debug
import Translator
from   GetArgs    import getargs
from   Upload     import data

if __name__ == "__main__":
    myargs = getargs([
        '--backup', 'filename',
        '--upload-backup', 'filename',
        '-u', '--upload',
        '-v', '--verbose',
        '--test',
        '--show', 'addr', 'size',
    ])
    args   = myargs.getargs()

    if '-v' in args or '--verbose' in args:
        Debug.will_print = True
        Debug.Print_nline("Verbose on", 4)

    COM.initialize()

    if '--backup' in args:
        Debug.Print_nline("Downloading MidiStomp Backup..", 1)
        filename = args['filename'].split('.')[0]

        with open(f"{filename}.ms2", "wb") as f:
            for i in range(4):
                print(f" - Saving.. {int(((i*16000)/64000)*100)}%", end="\r", flush=True)
                f.write(COM.read_block(i*16000, 16000))
        Debug.Print_nline("Complete!")

    elif '--show' in args:
        Debug.Print_nline(COM.read_block(int(args['addr']), int(args['size'])), 1)

    elif '-u' in args or '--upload' in args:
        Debug.Print_nline("Uploading MidiStomp Map..", 1)
        Translator.all(data)
        Debug.Print_nline("Complete!")

    # upload binary file backup
    elif '--upload-backup' in args:
        Debug.Print_nline("Uploading MidiStomp Backup..", 1)
        filename, ext = args['filename'].split('.')

        if ext != "ms2":
            raise Exception("File needs to be *.ms2..")

        with open(f"{filename}.ms2", "rb") as f:
            for i in range(1280):
                print(f" - Uploading.. {int(((i*50)/64000)*100)}%", end="\r", flush=True)
                COM.write_block(i*50, f.read(50))

        Debug.Print_nline("Complete!")
