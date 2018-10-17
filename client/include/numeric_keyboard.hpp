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
    static inline u32 _startX;
    static inline u32 _startY;

  public:
    static void show(u32 startX, u32 startY);
    static void hide();
    static void draw(Gui *gui);
    static inline std::string text = "";
    static inline bool shown = false;

    NumericKeyboard();
    ~NumericKeyboard();
};