#define MENU_MAIN          0
#define MENU_PRESET        1
#define MENU_PRESET_PARAMS 2
#define MENU_PRESET_PARAM  3
#define MENU_GLOBAL        4
#define MENU_PEDALS        5
#define MENU_PEDAL         6
#define MENU_COLORS        7
#define MENU_COLOR         8
#define MENU_FEATURES      9
#define MENU_FEATURE       10

struct Menu {
  // Variables we need
  //   - number of options
  //   - start address of options
  //   - size inbetween options
  // On complete, selected option returns:
  //   - either editor or another menu
  //   - number of options
  //   - start address of options
  //   - size inbetween options
  // Also create menus for the ListLoop, we can store the vars
  // for start address, size, and num options there

  // Need a global var to store the section of eeprom that we are trying to edit

  BUILD_OBJ_NAME(M_MENUS, MENU_SZ);
  BUILD_OBJ_VARIABLE(num_options, uint8_t,  M_MENUS, MENU_SZ, 13);
  BUILD_OBJ_VARIABLE(start_addr,  uint16_t, M_MENUS, MENU_SZ, 14);
  BUILD_OBJ_VARIABLE(size,        uint8_t,  M_MENUS, MENU_SZ, 16);
  BUILD_OBJ_VARIABLE(return_id,   uint8_t,  M_MENUS, MENU_SZ, 17); // gives the ID of the menu to return to

  // For list-loop selection, we need to know what menu to go to after
  // This is only needed IF start_addr is not inside M_OPTIONS partition
  BUILD_OBJ_VARIABLE(forward_id, uint8_t, M_MENUS, MENU_SZ, 18);

  // - callback id to run every time we switch between options, ie. for changing the LED
  //   colors when switching between color choices
  // - This is also used to build the option name when inside of a list-loop, ie.
  //   preset params, pedals, fsw params, etc.
  BUILD_OBJ_VARIABLE(callback_run_id, uint8_t, M_MENUS, MENU_SZ, 19);
  // - This is used to create the menu name for PresetParam edit and FSWParam Edit, ie.
  //   when changing a pedal for a PresetParam, we want to update the title of the edit menu to
  //   the newly selected pedal and feature.
  BUILD_OBJ_VARIABLE(callback_setup_id, uint8_t, M_MENUS, MENU_SZ, 20);

  // Only delete the latest parent[x] when the menu start_addr is not in M_OPTIONS partition

  // need var to know if we are in a standard menu with standard options or
  // if we are in a list-loop and need a different action on the way out
  //   - ListLoop
  //     - Object eeprom address selected goes in global var
  //     - need a var in the menu object to know what menu to jump to next
};

#define RESULT_MENU       0
#define RESULT_CONFIRM    1
#define RESULT_TEXT_EDIT  2
#define RESULT_VALUE_EDIT 3
#define RESULT_COLOR_EDIT 4
#define RESULT_MIDI_EDIT  5

struct Option {
  BUILD_OBJ_NAME_1_PARENT(M_OPTIONS, OPTION_SZ, NUM_OPTIONS_PER_MENU);

  // menu, confirm, textEdit, valueEdit, colorEdit, midiEdit, ColorSelect, PedalSelect, PedalParamSelect.. ?
  BUILD_OBJ_VARIABLE_1_PARENT(result,      uint8_t, M_OPTIONS, OPTION_SZ, 13, NUM_OPTIONS_PER_MENU);
  // menu id of next menu item
  BUILD_OBJ_VARIABLE_1_PARENT(menu_id,     uint8_t, M_OPTIONS, OPTION_SZ, 14, NUM_OPTIONS_PER_MENU);
  // callback id to run on selection of this option, before switching to next menu
  BUILD_OBJ_VARIABLE_1_PARENT(callback_id, uint8_t, M_OPTIONS, OPTION_SZ, 15, NUM_OPTIONS_PER_MENU);
};






#ifdef NOTES

- Need 2 parents
uint16_t parent[2] = { 0 };

- What do we know for TextEdit:
  - ALL texts that we are going to be editing are the first 13 bytes of a struct
  - SO if we do have the start location of a struct and we enter into a textEdit,
    it will ALWAYS edit the 13 bytes at the start location.

- What do we know for ValueEdit:
  - We will have the eeprom start address for the struct
  - We can add a variable to the menu option to add bytes to the start address to get
    the location of the byte we are trying to edit.. ie:
      - Select pedal, this puts start address in global parent variable
      - Scroll thru pedal settings menu and select CHANNEL option
      - This option has an extra variable that tells the menu function this channel
        variable is at the 13th byte of the pedal struct.
      - When clicked, parent 2 variable is filled with the location of byte to be edited
      - ValueEdit opens and edits the selected structs variable

- ColorEdit
  - We will set the parent address as the first byte for the 3 channels
  - The color edit will pull in the 3 bytes from that address and edit those

- MidiEdit (CBOBOX)
  - Same thing as the ColorEdit, except the options will be stored in the editor as
    F("NOTE"), F("CC"), F("PC"), etc.  This macro stores the strings in the Arduino
    eeprom on the chip to reduce program size.
  - When that option is selected, its corrolated integer value is stored at the 
    eeprom address.

- Color/Pedal/PedalParam Select
  - If the option is selected in the menu options, this will be hard-coded in the
    menu function.  If Color is selected, it will iterate thru the color choices and
    return the ID of the color selected.  This ID will be written into the byte of
    the eeprom address globally recorded.
  - These select menus will start on the number that is already selected,  If none is
    selected, then it starts on 0.

- Preset Param Edit
  - When in the preset menu, if you select 'PARAMS', we need a callback function to
    find the eeprom address of the first PresetParam to start looping from.

- Have the parent field as the start address of the object so..
  when you enter the Preset menu and select the 'name' option,
  the program takes the option text and sets that as the title 

- looping through pedals
  - once we select a pedal, that pedal number is set as the first parent
  - 


#endif
