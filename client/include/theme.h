#pragma once

#include <switch.h>
#include "types.h"

typedef struct {
  color_t textColor;
  color_t backgroundColor;
  color_t backgroundColorSemi;
  color_t highlightColor;
  color_t selectedColor;
  color_t separatorColor;
  color_t selectedButtonColor;
  color_t keyboardBackgroundColor;
  color_t keyboardButtonBackgroundColor;
} theme_t;

extern theme_t currTheme;

void setTheme(ColorSetId colorSetId);
