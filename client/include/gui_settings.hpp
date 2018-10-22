#pragma once

#include "gui.hpp"

#include <vector>
#include <unordered_map>

#define MENU_SCROLL_SPEED 40

class GuiSettings : public Gui {
public:
  GuiSettings();
  ~GuiSettings();

  static inline bool g_shouldUpdate = false;

  void update();
  void draw();
  void onInput(u32 kdown);
  void onTouch(touchPosition &touch);
  void onGesture(touchPosition &startPosition, touchPosition &endPosition);
  void save();

private:
  std::string ip_address = "";
  std::string port = "";
};
