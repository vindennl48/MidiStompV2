import COM
import Debug
import eeprom_map as emap

def all(data):
    Debug.Print_nline("Uploading Colors..")
    colors(data)

    Debug.Print_nline("Uploading Pedals..")
    pedals(data)

    # Debug.Print_nline("Uploading Menus..")
    # menus(data)

def colors(data):
    if "colors" in data:
        for color in data["colors"]:
            # Make sure we have an ID
            if "id" not in color:
                raise Exception("'id' property is needed in colors!")

            addr = emap.MAP_COLOR + (int(color["id"]) * emap.COLOR_SZ)

            if "name" in color:
                COM.write_block(
                    addr,
                    COM.text_fix( color["name"] )
                )

            if "channels" in color:
                COM.write_block(
                    addr + 13,
                    bytearray( color["channels"] )
                )

def pedals(data):
    if "pedals" in data:
        for pedal in data["pedals"]:
            # Make sure we have an ID
            if "id" not in pedal:
                raise Exception("'id' property is needed in pedals!")

            addr = emap.MAP_PEDAL + (int(pedal["id"]) * emap.PEDAL_SZ)

            Debug.Print_nline(f"pedal addr: {addr}")

            if "name" in pedal:
                COM.write_block(
                    addr,
                    COM.text_fix( pedal["name"] )
                )

            if "channel" in pedal:
                COM.write_block(
                    addr + 13,
                    bytearray( pedal["channel"] )
                )

            if "features" in pedal:
                features(pedal)

def features(pedal):
    if "features" in pedal:
        for feature in pedal["features"]:
            # Make sure we have an ID
            if "id" not in pedal:
                raise Exception("'id' property is needed in features!")

            addr = emap.MAP_FEATURE + (( ( int(pedal["id"]) * emap.NUM_FEATURES_PER_PEDAL ) + int(feature["id"]) ) * emap.FEATURE_SZ)

            if "name" in feature:
                COM.write_block(
                    addr,
                    COM.text_fix( feature["name"] )
                )

            if "type" in feature:
                feature_type = 0
                if feature["type"] == "NOTE":
                    feature_type = emap.MIDI_TYPE_NOTE
                elif feature["type"] == "CC":
                    feature_type = emap.MIDI_TYPE_CC
                elif feature["type"] == "PC":
                    feature_type = emap.MIDI_TYPE_PC
                else:
                    raise Exception(f"Feature needs correct type! '{feature['name']}'")

                COM.write_block(
                    addr + 13,
                    bytearray( feature_type )
                )

            if "pitch" in feature:
                COM.write_block(
                    addr + 14,
                    bytearray( feature["pitch"] )
                )

def presets(data):
    pass

def menus(data):
    if "menus" in data:
        for menu in data["menus"]:
            # Make sure we have an ID
            if "id" not in menu:
                raise Exception("'id' property is needed in menus!")

            addr = emap.MAP_MENU + (int(menu["id"]) * emap.MENU_SZ)

            if "name" in menu:
                COM.write_block(
                    addr,
                    COM.text_fix( menu["name"] )
                )

            if "num_options" in menu:
                COM.write_block(
                    addr + 13,
                    bytearray( menu["num_options"] )
                )

            if "options" in menu:
                options(menu)

def options(menu):
    if "options" in menu:
        for option in menu["options"]:
            # Make sure we have an ID
            if "id" not in option:
                raise Exception("'id' property is needed in options!")

            addr = emap.MAP_OPTION + (( ( int(menu["id"]) * emap.NUM_OPTIONS_PER_MENU ) + int(option["id"]) ) * emap.OPTION_SZ)

            if "name" in option:
                COM.write_block(
                    addr,
                    COM.text_fix( option["name"] )
                )
