#include <Arduino.h>
#include "Helpers.h"
#include "I2C_EPROM.h"

/* :: TEXT :: */
Text::Text() : sz(0) {
  text[TEXT_SZ] = {' '};
}

void Text::operator = (Text &t) {
  memcpy(text, t.text, TEXT_SZ);
}
template <int N>
Text& Text::operator += (const char (&c)[N]) {
  for (int i=0, j=sz; i<N, j<TEXT_SZ-1; i++, j++) {
      text[j] = c[i];
      sz++;
  }
}
Text& Text::operator += (Text &t) {
  for (int i=0, j=sz; i<t.sz, j<TEXT_SZ-1; i++, j++) {
      text[j] = t[i];
      sz++;
  }
}
char& Text::operator [] (int i) {
  if ( i > sz ) i = 13;  // if out of range, return null terminated
  return text[i];
}
template <int N>
void Text::set_text(const char (&c)[N]) {}

String Text::str() { return String(text); }

Text buffer[2];  // Text buffer for lcd display
/* :: END TEXT :: */


/* :: OBJNAME :: */
uint16_t addr() { return 0; } // needs to be overloaded by host

Text ObjName::name() {
  return EPROM::read_text( addr() );
}

void ObjName::set_name(Text text) {
  EPROM::write_text( addr(), text );
}
/* :: END OBJNAME :: */


