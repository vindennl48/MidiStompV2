#ifndef HELPERS_H
#define HELPERS_H

/* DEFINITIONS */
#define TEXT_SZ 13
/* END DEFINITIONS */

/* MACROS */
#define MOD(absolute, div_by) ((absolute+div_by)%div_by) // returns relative pos
/* END MACROS */

struct Text {
  char text[13];

  Text();

  void operator = (const Text&);

  template <int N>
  void set_text(char const (&)[N]);
};

struct ObjName {
  Text name();
  void set_name(Text);
};

#endif
