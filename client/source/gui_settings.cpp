#include "gui_settings.hpp"

#include <string>
#include <sstream>
#include <math.h>

enum  {
  NUMERIC_KEYBOARD_SHOWN,
  NUMERIC_KEYBOARD_HIDDEN
} numericKeyboardState = NUMERIC_KEYBOARD_HIDDEN;

GuiSettings::GuiSettings() : Gui() {
}

GuiSettings::~GuiSettings() {
}

void GuiSettings::update() {
    Gui::update();
}

void GuiSettings::draw() {
    Gui::beginDraw();
    Gui::drawRectangle(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColor);
    Gui::drawText(font24, 50, 50, currTheme.textColor, "SwitchDL Settings");
    Gui::drawRectangle(50, 90, 260, 2, currTheme.textColor);

    Gui::drawText(font24, 50, 160, currTheme.textColor, "IP Address:");
    Gui::drawBorderedRectangle(250, 160, 350, 50, 1, currTheme.textColor, currTheme.backgroundColor);
    Gui::drawText(font24, 50, 230, currTheme.textColor, "Port:");
    Gui::drawBorderedRectangle(250, 230, 200, 50, 1, currTheme.textColor, currTheme.backgroundColor);

    Gui::drawTextAligned(font20, Gui::g_framebuffer_width - 50, Gui::g_framebuffer_height - 50, currTheme.textColor, "\uE0E1 Back     \uE0E0 Save", ALIGNED_RIGHT);
    Gui::endDraw();
}

void GuiSettings::onInput(u32 kdown) {
    printf("asdasdas\n");
    if (kdown & KEY_A) {
        if (numericKeyboardState == NUMERIC_KEYBOARD_HIDDEN) {
            printf("A CLICKED\n");
        }
    }
}

void GuiSettings::onTouch(touchPosition &touch) {
}

void GuiSettings::onGesture(touchPosition &startPosition, touchPosition &endPosition) {
}
