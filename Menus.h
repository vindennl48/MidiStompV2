#ifndef MENUS_H
#define MENUS_H

#include "Menu.h"
#include "MenuSelect.h"

MenuInput menu_input_gbl_settings[] = {
  {"::GBL SETTINGS::", MenuDummy},
  {"MIDI",             MenuDummy},
  {"DEVICES",          MenuDummy},
  {"BACK",             MenuBack}
};
MenuSelect<MenuInput, 4> menu_gbl_settings(&menu_input_gbl_settings);

MenuInput menu_input_settings[] = {
  {"::SETTINGS::", MenuDummy},
  {"NAME",         MenuDummy},
  {"BPM",          MenuDummy},
  {"GBL SETTINGS", menu_gbl_settings},
  {"BACK",         MenuBack}
};
MenuSelect<MenuInput, 5> menu_settings(&menu_input_settings);

//#define MS_NAME        1
//#define MS_BPM         2
//#define MS_SWITCHES    3
//#define MS_GBLSETTINGS 4
//#define MS_BACK        5
//String menu_settings_list[] = {"::SETTINGS::", "NAME", "BPM", "SWITCHES", "GBL SETTINGS", "BACK"};
//MenuSelect<String, LEN(menu_settings_list)> menu_settings(&menu_settings_list);

//#define MG_DEVICES       1
//#define MG_MIDI_NOTES    2
//#define MG_COLORS        3
//#define MG_FACTORY_RESET 4
//#define MG_BACK          5
//String menu_global_list[] = {"::GBL SETTINGS::", "DEVICES", "MIDI NOTES", "COLORS", "FACTORY RESET", "BACK"};
//MenuSelect<String, LEN(menu_global_list)> menu_global(&menu_global_list);


#endif
