# Settings Menu
  - When long-pressing the encoder, you have access to the settings menu
  - On screen, you have direct access to:
    - Naming the current preset
    - Saving the current preset (if there are changes)
    - Changing the Preset loading MIDI notes
      - When changing presets, a list of MIDI notes get sent out
        to turn on specific pedals for that preset.
    - Copy Preset to another preset
    - Reset Preset
    - Go to Global Settings menu
      - Change Pedals
        - Change Pedal Name
        - Change MIDI Channel
        - Change parameters
          - Change Param Name
          - Change Param MIDI Note
      - Change Colors
        - Change Color Name
        - Change Color values
      - Factory Reset
  - To change the footswitch settings, simply click on the pedal you want to
    edit.
    - Change footswitch activation type: OFF / TOGGLE / CYCLE / ONESHOT
    - Change Colors for OFF, ON1, ON2
    - Change Parameter to affect when is_pressed is activated OR switch to sub-menu
      - set velocity value / patch value
    - Change Parameter to affect when is_long_pressed is activated OR switch to sub-menu
      - set velocity value / patch value
      
## Menu Breakdown
  - ::SETTINGS
  - > SAVE  (if there were changes)
  -   NAME
  -   PARAMS
  -   COPY
  -   RESET
  -   GLOBAL

  - ::GLOBAL
  - > PEDALS
      - NAME
      - CHANNEL
      - PARAMS
        - NAME
        - MIDI
  -   COLORS
      - NAME
      - VALUES
  -   RESET

  - ::FSW 1
  - > TYPE
  -   COLORS
  -   SHORT PRESS
  -   LONG PRESS

## List of words
  - SETTINGS
  - SAVE
  - NAME
  - PARAMS
  - COPY
  - RESET
  - GLOBAL
  - PEDALS
  - CHANNEL
  - MIDI
  - COLORS
  - VALUES
  - FSW ( take out for space )
  - TYPE
  - SHORT PRESS
  - LONG PRESS


# OLD --------------------------------------------------------------------------

# ToDo List
  - DONE:: Create a text editor on the screen with encoder
  - DONE:: Create a quick menu for editing the database entries
    - 'SETTINGS'->'DEVICES'
    - 'SETTINGS'->'MIDI NOTES'
    - 'SETTINGS'->'COLORS'
    - 'SETTINGS'->'FACTORY RESET'
  - Create Database struct
    - EEPROM read/write
    - model/database structure
    - make Presets last on EEPROM so we can change the
      size of this without messing with the other models
  - Start the outline of the Preset struct
    - Get this saving into the database
  - Create Menu struct
    - Start integrating it into the Preset struct
  - Create Footswitch struct
    - Start integrating this into the menu struct
    - Remember to create struct for switching presets by pressing
      the middle footswitch with one of the outside footswitches
      - This will only be possible if quick_press is off
  - Create LED struct


# FootSwitch
  ## Regular Press & Long Press
  - One Shot / Toggle / Cycle Thru
    - One Shot   - Select the same midi note for OFF and ON1
    - Toggle     - Select an OFF and ON1 value to toggle between
    - Cycle Thru - Select an OFF value and a ON1, ON2 value
  - Momentary ( NO LONG PRESS )
    - Hold down to activate ON1 value, let go to activate OFF value
  - Go into Sub Menu / back out of Sub Menu
  - Switch Preset / preset # select
  
  struct Press{
    // toggle / momentary / submenu / preset,
    // off ( submenu 0,1,2,3 / preset# ), on1, on2,
    
    uint8_t state       = 0; // 0 = toggle, 1 = momentary, 2 = submenu, 3 = preset
    bool    quick_press = false;  // if true, NO LONG PRESS
    uint8_t color_id [ off, on1, on2 ]; // momentary mode turns all the LEDs the same color
    union {
      midi off [ struct midi { pedal_id(0=NONE), param_id, value: 0-127 } ],
      uint8_t submenu = 0,
      uint8_t preset = 0,
    }
    midi on1 [ struct midi { pedal_id(0=NONE), param_id, value: 0-127 } ],
    midi on2 [ struct midi { pedal_id(0=NONE), param_id, value: 0-127 } ],
    
    // Add function to reset union when changing state
  }
  
  
# Menu/SubMenu
  - 1 main menu, 3 sub-menus
  - 4 footswitches per menu
  - Pedal
    - two colors per pedal
      - first color is on color
      - second color is off color
      - If no option is set for off color, when selected, it will only blink
      - If option is selected for off color, then when selected, it will
        alternate between on-off color

  
# Preset
  - Name: "Slough"
  - BPM:  120
  - midi command [ struct midi { pedal_id(0=NONE), param_id, value: 0-127 } ] x20,
    - These trigger when the preset is activated
  - submenus: [ submenu0, submenu1, submenu2, submenu3 ]
 
 
# MIDI SYNC
  - Need to do SMTP timecode sync with Studio One, but also Midi Time
    Code sync with the pedals.  Need to figure out how to do both..
 
  
# Database
  ## Models
  - Database Settings
    - database version number
      - Used for making sure if there is an upgrade, we don't accidentally overwrite
        important data.  For example: if we add a variable to the 'Presets' model, all
        data after the first preset will become corrupt.  This will afford us the
        opportunity to run a program to add in the variable without corruption.
  - Midi
    - ID: 1-256. { Note/CC/PC, Note } // Velocity will be in footswitch, (0=NONE)
  - Pedals/Devices
    - ID: 1-9. { Pedal Name: "UNTITLED", Channel: 0, parameters: 1-28. [ parameter name: "PARAM1", midi_id: 1-256(from above)(0=NONE) ] } (0=NONE)
  - LED Colors
    - ID: 1-64. { name: "GREEN_H" (_H for bright, _L for dim), value: struct color{ union{ uint12_t value, struct{ r:16, g:16, b:16 } } } }
  - Presets
    - ID: 1-64. { name: "SLOUGH", bpm: 120, midi_command: [ pedal_id, param_id, value ]x20, sub_menu: [ menu1 - menu4 ] }

# HARDWARE
  ## Midi Loop
  Starts with Focusrite Out -> Midi Stomp In -> Midi Stomp Out -> 
