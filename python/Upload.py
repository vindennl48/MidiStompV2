data = {}


data["colors"] = [
    {"id": 0,  "name": "red_off",     "channels": [2,   0,   0]},
    {"id": 1,  "name": "red_on",      "channels": [255, 0,   0]},

    {"id": 2,  "name": "green_off",   "channels": [0,   2,   0]},
    {"id": 3,  "name": "green_on",    "channels": [0,   255, 0]},

    {"id": 4,  "name": "blue_off",    "channels": [0,   0,   2]},
    {"id": 5,  "name": "blue_on",     "channels": [0,   0,   255]},

    {"id": 6,  "name": "lt_blue_off", "channels": [0,   0,   0]},
    {"id": 7,  "name": "lt_blue_on",  "channels": [0,   0,   0]},

    {"id": 8,  "name": "yellow_off",  "channels": [0,   0,   0]},
    {"id": 9,  "name": "yellow_on",   "channels": [0,   0,   0]},

    {"id": 10, "name": "purple_off",  "channels": [0,   0,   0]},
    {"id": 11, "name": "purple_on",   "channels": [0,   0,   0]},

    {"id": 12, "name": "orange_off",  "channels": [0,   0,   0]},
    {"id": 13, "name": "orange_on",   "channels": [0,   0,   0]},
]


data["pedals"] = [
    {
        "id"      : 0,
        "name"    : "HXSTOMP",
        "channel" : 1,
        "features": [
            {"id": 0, "name": "FS1", "type": "CC", "pitch": 49},
            {"id": 1, "name": "FS2", "type": "CC", "pitch": 50},
            {"id": 2, "name": "FS3", "type": "CC", "pitch": 51},
            {"id": 3, "name": "FS4", "type": "CC", "pitch": 52},
            {"id": 4, "name": "FS5", "type": "CC", "pitch": 53},
        ]
    },
    {
        "id"      : 1,
        "name"    : "ADAM",
        "channel" : 2,
        "features": [
            {"id": 0, "name": "CLEAN1", "type": "PC", "pitch": 0},
            {"id": 1, "name": "DIST1",  "type": "PC", "pitch": 1},
            {"id": 2, "name": "FUZZ1",  "type": "PC", "pitch": 2},
        ]
    },
    {
        "id"      : 2,
        "name"    : "MICROCOSM",
        "channel" : 3,
        "features": [
            {"id": 0, "name": "BYPASS", "type": "CC", "pitch": 12},
        ]
    },
    {
        "id"      : 3,
        "name"    : "TEMPUS",
        "channel" : 4,
        "features": [
            {"id": 0, "name": "BYPASS",   "type": "CC", "pitch": 23},
            {"id": 1, "name": "ROOM",     "type": "PC", "pitch": 16},
            {"id": 2, "name": "SPATIUM",  "type": "PC", "pitch": 17},
            {"id": 3, "name": "INFINITE", "type": "PC", "pitch": 18},
        ]
    },
]
