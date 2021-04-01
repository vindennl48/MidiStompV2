#ifndef MENUS_H
#define MENUS_H

#include "Menu.h"
#include "MenuMidiNotes.h"
#include "MenuDevices.h"

/* ::GLOBAL SETTINGS:: */
#define MENU_GBLSETTINGS_SZ 6
String menu_gblsettings_options[MENU_GBLSETTINGS_SZ] = {
  "::GBL SETTINGS::",
  "DEVICES",
  "MIDI_NOTES",
  "COLORS",
  "FACTORY RESET",
  "BACK"
};
f_menuResult menu_gblsettings_options_f[MENU_GBLSETTINGS_SZ-1] = {
  menuDevices,
  menuMidiNotes,
  MenuDummy,
  MenuDummy,
  MenuBack
};
MenuSelect menu_gblsettings;
uint8_t menuGblSettings() {
  return menu_gblsettings.loop(
    menu_gblsettings_options,
    menu_gblsettings_options_f,
    MENU_GBLSETTINGS_SZ
  );
}
/* ::END GLOBAL SETTINGS:: */


/* ::SETTINGS:: */
#define MENU_SETTINGS_SZ 6
String menu_settings_options[MENU_SETTINGS_SZ] = {
  "::SETTINGS::",
  "NAME",
  "BPM",
  "SWITCHES",
  "GBL SETTINGS",
  "BACK"
};
f_menuResult menu_settings_options_f[MENU_SETTINGS_SZ] = {
  MenuDummy,
  MenuDummy,
  MenuDummy,
  menuGblSettings,
  MenuBack
};
MenuSelect menu_settings;
uint8_t menuSettings() {
  return menu_settings.loop(
    menu_settings_options,
    menu_settings_options_f,
    MENU_SETTINGS_SZ
  );
}
/* ::END SETTINGS:: */


#endif
