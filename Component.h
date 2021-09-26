#ifndef COMPONENT_H
#define COMPONENT_H

// Header

// CPP
#define COMPONENT_CREATE_FUNC_HD_START(object, start) \
  uint16_t ##object::hd_start() { \
    return start; \
  }

#define COMPONENT_CREATE_FUNC_NAME(object) \
  void ##object::name(uint8_t buffer=TXT_BUF_1) { \
    eReadBlock(addr(), (uint8_t*)text[buffer], sizeof(TEXT_SZ)); \
  }

#define COMPONENT_CREATE_FUNC_ADDR(object) \
  uint16_t ##object::addr(uint8_t id) { \
    return GET_PARENT(hd_start(), id, sizeof(object)) \
  }

#define COMPONENT_CREATE_FUNC_ALL(object, start) \
  COMPONENT_CREATE_FUNC_HD_START(object, start); \
  COMPONENT_CREATE_FUNC_NAME(object); \
  COMPONENT_CREATE_FUNC_ADDR(object)

#endif
