#pragma once

#include <stdio.h>
#include <math.h>
#include <sstream>
#include <iostream>

extern "C" {
  #include "types.h"
}

class Gui;

class NumericKeyboard
{
  private:
    static inline std::string edit_display_string = "";
    static inline std::string caption_display_string = "";
    static inline ColorSetId colorSetId;
    static inline color_t deleteBackgroundColor;
    static inline color_t deleteTextColor;
    static inline color_t OKBackgroundColor;
    static inline color_t OKTextColor;
    static inline void deleteCharacter();
    static inline void ok();

  public:
    static void show(std::string caption);
    static void hide();
    static void onTouch(touchPosition &touch);
    static void onInput(u32 keydown);
    //static void onGesture(touchPosition &startPosition, touchPosition &endPosition);

    static void draw(Gui *gui);
    static inline std::string *bind_value;
    static inline std::string text = "";
    static inline bool shown = false;

    NumericKeyboard();
    ~NumericKeyboard();
};