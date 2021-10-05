#ifndef HELPERS_H
#define HELPERS_H

/* DEFINITIONS */
#define TEXT_SZ 13
/* END DEFINITIONS */

/* MACROS */
#define MOD(absolute, div_by) ((absolute+div_by)%div_by) // returns relative pos
/* END MACROS */

struct ObjName {
  uint16_t addr();
  String   name();
  void     set_name(String);
};

#endif
