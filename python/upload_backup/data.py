
data = {
    "colors": [
        { "name": "RED_ON",     "r": 0, "g": 0, "b": 0 },
        { "name": "RED_OFF",    "r": 0, "g": 0, "b": 0 },
        { "name": "ORANGE_ON",  "r": 0, "g": 0, "b": 0 },
        { "name": "ORANGE_OFF", "r": 0, "g": 0, "b": 0 },
        { "name": "GREEN_ON",   "r": 0, "g": 0, "b": 0 },
        { "name": "GREEN_OFF",  "r": 0, "g": 0, "b": 0 },
        { "name": "BLUE_ON",    "r": 0, "g": 0, "b": 0 },
        { "name": "BLUE_OFF",   "r": 0, "g": 0, "b": 0 },
        { "name": "YELLOW_ON",  "r": 0, "g": 0, "b": 0 },
        { "name": "YELLOW_OFF", "r": 0, "g": 0, "b": 0 },
        { "name": "PURPLE_ON",  "r": 0, "g": 0, "b": 0 },
        { "name": "PURPLE_OFF", "r": 0, "g": 0, "b": 0 },
    ],

    "pedals": [
        {
            "name": "STOMP",
            "channel": 1,
            "features": [
                { "name": "FS1", "type": "CC", "pitch": 49 },
                { "name": "FS2", "type": "CC", "pitch": 50 },
                { "name": "FS3", "type": "CC", "pitch": 51 },
                { "name": "FS4", "type": "CC", "pitch": 52 },
                { "name": "FS5", "type": "CC", "pitch": 53 },
            ]
        },
    ],

#    presets: [
#        {
#            name: "STEEL",
#            parameters: [
#                { pedal: "STOMP", feature: "FS1", velocity: 127 },
#            ],
#            fsw_menu: [
#                [   # MENU 1
#
#                    {   # FSW1
#                        mode: "TOGGLE",
#                        press_type: "UP",
#                        state: [
#                            {
#                                color: "RED_OFF",
#                                parameters: [
#                                    { pedal: "STOMP", feature: "FS1", velocity: 127 },
#                                ]
#                            },
#                            {
#                                color: "RED_ON",
#                                parameters: [
#                                    { pedal: "STOMP", feature: "FS1", velocity: 0 },
#                                ]
#                            },
#                        ]
#                    },
#
#                    {   # FSW2
#                        mode: "TOGGLE",
#                        press_type: "UP",
#                        state: [
#                            {
#                                color: "RED_OFF",
#                                parameters: [
#                                    { pedal: "STOMP", feature: "FS1", velocity: 127 },
#                                ]
#                            },
#                            {
#                                color: "RED_ON",
#                                parameters: [
#                                    { pedal: "STOMP", feature: "FS1", velocity: 0 },
#                                ]
#                            },
#                        ]
#                    },
#
#                    {   # FSW3
#                        mode: "TOGGLE",
#                        press_type: "UP",
#                        state: [
#                            {
#                                color: "RED_OFF",
#                                parameters: [
#                                    { pedal: "STOMP", feature: "FS1", velocity: 127 },
#                                ]
#                            },
#                            {
#                                color: "RED_ON",
#                                parameters: [
#                                    { pedal: "STOMP", feature: "FS1", velocity: 0 },
#                                ]
#                            },
#                        ]
#                    },
#                ],
#            ]
#        }
#    ]
}
