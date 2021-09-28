#include <Arduino.h>
#include "Helpers.h"

/* :: TEXT :: */
Text::Text() {
  text[TEXT_SZ] = {' '};
}

void Text::operator = (const Text &t) {
  memcpy(text, t.text, TEXT_SZ);
}
template <int N>
void Text::set_text(char const (&c)[N]) {}
/* :: END TEXT :: */


/* :: OBJNAME :: */
Text ObjName::name() {}
void ObjName::set_name(Text text) {}
/* :: END OBJNAME :: */


