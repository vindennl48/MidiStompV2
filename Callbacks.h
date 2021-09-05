uint8_t f_colors() {
  // Set the LED colors to match the selected color
  uint8_t color_id = GET_ID_FROM_ADDR(M_COLORS, parents[1], COLOR_SZ);
  leds_set(
    Color::get_red(color_id),
    Color::get_green(color_id),
    Color::get_blue(color_id)
  );

  return true;
}

#define F_NONE   0
#define F_COLORS 1

typedef uint8_t (*Callback)();

Callback get_callback(uint8_t id) {
  switch(id) {
    case F_COLORS: return &f_colors;
  };

  return nullptr;
}
