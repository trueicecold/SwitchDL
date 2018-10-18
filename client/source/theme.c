#include "theme.h"

#pragma GCC diagnostic ignored "-Wmissing-braces"

theme_t currTheme;

void setTheme(ColorSetId colorSetId) {
  switch (colorSetId) {
    case ColorSetId_Light:
      currTheme = (theme_t) {
        .textColor                      =      RGBA8(0x00, 0x00, 0x00, 0xFF),
        .backgroundColor                =      RGBA8(0xEA, 0xEA, 0xEA, 0xFF),
        .backgroundColorSemi            =      RGBA8(0xEA, 0xEA, 0xEA, 0xE8),
        .highlightColor                 =      RGBA8(0x27, 0xA3, 0xC7, 0xFF),
        .selectedColor                  =      RGBA8(0x50, 0x2D, 0xE4, 0xFF),
        .separatorColor                 =      RGBA8(0x60, 0x60, 0x60, 0x80),
        .selectedButtonColor            =      RGBA8(0xFD, 0xFD, 0xFD, 0xFF),
        .keyboardBackgroundColor        =      RGBA8(0xDE, 0xDE, 0xDE, 0xFF),
        .keyboardButtonBackgroundColor  =      RGBA8(0xD6, 0xD6, 0xD6, 0xFF),
        .keyboardDeleteBackgroundColor  =      RGBA8(0x37, 0x37, 0x37, 0xFF),
        .keyboardDeleteTextColor        =      RGBA8(0xFF, 0xFF, 0xFF, 0xFF),
        .keyboardOKBackgroundColor      =      RGBA8(0x39, 0x55, 0xDD, 0xFF),
        .keyboardOKTextColor            =      RGBA8(0xBF, 0xCA, 0xFF, 0xFF)
      };
      break;
    case ColorSetId_Dark:
      currTheme = (theme_t) {
        .textColor                      =      RGBA8(0xFF, 0xFF, 0xFF, 0xFF),
        .backgroundColor                =      RGBA8(0x31, 0x31, 0x31, 0xFF),
        .backgroundColorSemi            =      RGBA8(0x31, 0x31, 0x31, 0xE8),
        .highlightColor                 =      RGBA8(0x27, 0xA3, 0xC7, 0xFF),
        .selectedColor                  =      RGBA8(0x59, 0xED, 0xC0, 0xFF),
        .separatorColor                 =      RGBA8(0x60, 0x60, 0x60, 0x80),
        .selectedButtonColor            =      RGBA8(0x25, 0x26, 0x2A, 0xFF),
        .keyboardBackgroundColor        =      RGBA8(0x46, 0x46, 0x46, 0xFF),
        .keyboardButtonBackgroundColor  =      RGBA8(0x4F, 0x4F, 0x4F, 0xFF),
        .keyboardDeleteBackgroundColor  =      RGBA8(0xFF, 0xFF, 0xFF, 0xFF),
        .keyboardDeleteTextColor        =      RGBA8(0x34, 0x34, 0x34, 0xFF),
        .keyboardOKBackgroundColor      =      RGBA8(0x77, 0xFC, 0xCD, 0xFF),
        .keyboardOKTextColor            =      RGBA8(0x12, 0x45, 0x34, 0xFF)
      };
      break;
  }
}
