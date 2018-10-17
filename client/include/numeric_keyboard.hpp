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
    static inline std::string display_string = "";

  public:
    static void show();
    static void hide();
    static void draw(Gui *gui);
    static inline std::string *bind_value;
    static inline std::string text = "";
    static inline bool shown = false;

    NumericKeyboard();
    ~NumericKeyboard();
};