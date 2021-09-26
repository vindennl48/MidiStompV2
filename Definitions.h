#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#define GET_PARENT(start, id, size) (start + (id * size))

#define NUM_PEDALS                   8
#define NUM_PRESETS                  20
#define NUM_PRESET_PARAMS_PER_PRESET 10
#define NUM_MENUS_PER_PRESET         4
#define NUM_PRESET_PARAMS_TOTAL      (NUM_PRESETS*NUM_PRESET_PARAMS_PER_PRESET)
#define NUM_FSW_PER_MENU             4
#define NUM_FSW_PER_PRESET           (NUM_MENUS_PER_PRESET*NUM_FSW_PER_MENU)
#define NUM_FSW_TOTAL                (NUM_FSW_PER_PRESET*NUM_PRESETS)
#define NUM_COLORS_PER_FSW           3

#define HD_START_PRESETS             0
#define HD_START_PRESET_PARAMS       (HD_START_PRESETS + (sizeof(Preset) * NUM_PRESETS) + 1)
#define HD_START_FSW_PARAMS          (HD_START_PRESET_PARAMS + (sizeof(PresetParam) * NUM_PRESET_PARAMS_PER_PRESET) + 1)

#define RAM_TEXT_MAX 2
#define TEXT_SZ      13
#define TXT_BUF_1    0
#define TXT_BUF_2    0

extern char text[RAM_TEXT_MAX][TEXT_SZ];

struct Preset;
struct Pedal;
struct Feature;
struct Fsw;
struct Param;
struct PresetParam;
struct FswParam;

#endif
