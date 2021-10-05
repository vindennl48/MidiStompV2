#ifndef MAIN_EVENTS_H
#define MAIN_EVENTS_H

#include "Nav.h"

#define E_SETUP        0
#define E_MAIN         1
#define E_SETTINGS     2
#define E_FSW_SETTINGS 3

void e_setup(Nav*);
void e_main(Nav*);
void e_settings(Nav*);
void e_fsw_settings(Nav*);

#endif
