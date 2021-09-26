# Basic Footswitches
distortion_cycle = {
    mode: "CYCLE",
    press_type: "UP",
    state: [
        {
            color: "ORANGE_OFF",
            parameters: [
                { pedal: "ADAM", feature: "DIST1", velocity: 127 },
            ],
        },
        {
            color: "ORANGE_ON",
            parameters: [
                { pedal: "ADAM", feature: "FUZZ1", velocity: 127 },
            ],
        },
        {
            color: "RED_ON",
            parameters: [
                { pedal: "ADAM", feature: "CLEAN1", velocity: 127 },
            ],
        },
    ],
    long_press: {
        mode: "OFF",
        parameters: [],
    },
}

reverb_cycle = {
    mode: "CYCLE",
    press_type: "UP",
    state: [
        {
            color: "BLUE_OFF",
            parameters: [
                { pedal: "TEMPUS", feature: "RVERB1", velocity: 127 },
            ],
        },
        {
            color: "BLUE_ON",
            parameters: [
                { pedal: "TEMPUS", feature: "INFINITE", velocity: 127 },
            ],
        },
        {
            color: "L_BLUE_ON",
            parameters: [
                { pedal: "TEMPUS", feature: "ROOM1", velocity: 127 },
            ],
        },
    ],
    long_press: {
        mode: "ONESHOT",
        parameters: [
            { pedal: "TEMPUS", feature: "BYPASS", velocity: 0 },
        ],
    },
}
