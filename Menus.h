#ifndef MENUS_H
#define MENUS_H

#include "Menu.h"
#include "MenuSelect.h"

#define MS_NAME        1
#define MS_BPM         2
#define MS_SWITCHES    3
#define MS_GBLSETTINGS 4
#define MS_BACK        5
String menu_settings_list[] = {"::SETTINGS::", "NAME", "BPM", "SWITCHES", "GBL SETTINGS", "BACK"};
MenuSelect<String, LEN(menu_settings_list)> menu_settings(&menu_settings_list);

#define MG_DEVICES       1
#define MG_MIDI_NOTES    2
#define MG_COLORS        3
#define MG_FACTORY_RESET 4
#define MG_BACK          5
String menu_global_list[] = {"::GBL SETTINGS::", "DEVICES", "MIDI NOTES", "COLORS", "FACTORY RESET", "BACK"};
MenuSelect<String, LEN(menu_global_list)> menu_global(&menu_global_list);


#endif
