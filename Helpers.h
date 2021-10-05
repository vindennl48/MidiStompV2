#ifndef HELPERS_H
#define HELPERS_H

/* DEFINITIONS */
#define TEXT_SZ 13
/* END DEFINITIONS */

/* MACROS */
#define MOD(absolute, div_by) ((absolute+div_by)%div_by) // returns relative pos
/* END MACROS */

#define TXT_BUF_1 0
#define TXT_BUF_2 1
struct Text {
  char    text[13];
  uint8_t sz;

  Text();

  void  operator =  (Text&);
  template <int N>
  Text& operator += (const char (&c)[N]);
  Text& operator += (Text&);
  char& operator [] (int);

  template <int N>
  void set_text(const char (&)[N]);

  String str();
};
extern Text buffer[2];  // Text buffer for lcd display

struct ObjName {
  uint16_t addr();
  Text name();
  void set_name(Text);
};

#endif
