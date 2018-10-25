#include "gui_main.hpp"

#include <string>
#include <sstream>
#include <math.h>

GuiMain::GuiMain() : Gui() {
}

GuiMain::~GuiMain() {
}

void GuiMain::update() {
  Gui::update();
}

void GuiMain::draw() {
  //printf("ENTER DRAW!\n");
  Gui::beginDraw();
  Gui::drawText(font24, 100, 100, currTheme.textColor, "Hello World!");
  Gui::drawRectangle(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColor);
  Gui::endDraw();
}

void GuiMain::onInput(u32 kdown) {
  static bool batchClicked = false;

  if (kdown & KEY_LEFT) {
  } else if (kdown & KEY_RIGHT) {
  } else if (kdown & KEY_UP) {
  } else if (kdown & KEY_DOWN) {
  }

  if (kdown & KEY_A) {
  }

  if (kdown & KEY_L) {
  }

  if (kdown & KEY_X) {
  }

  if (kdown & KEY_B) {
  }

  if (kdown & KEY_MINUS) {
  }
}

void GuiMain::onTouch(touchPosition &touch) {
}

void GuiMain::onGesture(touchPosition &startPosition, touchPosition &endPosition) {
  /*if (Title::g_titles.size() == 0) return;*/

}
