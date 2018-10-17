#include "gui_settings.hpp"

#include <string>
#include <sstream>
#include <math.h>

GuiSettings::GuiSettings() : Gui() {
}

GuiSettings::~GuiSettings() {
}

void GuiSettings::update() {
    Gui::update();
    /*if (NumericKeyboard::shown) {
        NumericKeyboard::update();
    }*/
}

std::string ip_address = "10.0.0.138";
std::string port = "9999";

void GuiSettings::draw() {
    Gui::beginDraw();
    Gui::drawRectangle(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColor);
    Gui::drawText(font24, 50, 50, currTheme.textColor, "SwitchDL Settings");
    Gui::drawRectangle(50, 90, 260, 2, currTheme.textColor);

    Gui::drawText(font24, 50, 160, currTheme.textColor, "IP Address:");
    Gui::drawBorderedRectangle(250, 160, 350, 50, 1, currTheme.textColor, currTheme.backgroundColor);
    Gui::drawText(font24, 260, 165, currTheme.textColor, ip_address.c_str());

    Gui::drawText(font24, 50, 230, currTheme.textColor, "Port:");
    Gui::drawBorderedRectangle(250, 230, 200, 50, 1, currTheme.textColor, currTheme.backgroundColor);
    Gui::drawText(font24, 260, 235, currTheme.textColor, port.c_str());

    Gui::drawTextAligned(font20, Gui::g_framebuffer_width - 50, Gui::g_framebuffer_height - 50, currTheme.textColor, "\uE0E1 Back     \uE0E0 Save", ALIGNED_RIGHT);
    Gui::endDraw();
}

void GuiSettings::onInput(u32 kdown) {
    if (kdown & KEY_A) {
        NumericKeyboard::show();
    }
}

void GuiSettings::onTouch(touchPosition &touch) {
    if (touch.px >= 250 && touch.px <= 600 && touch.py >= 160 && touch.py <= 210) {
        NumericKeyboard::bind_value = &ip_address;
        NumericKeyboard::show();
    }
}

void GuiSettings::onGesture(touchPosition &startPosition, touchPosition &endPosition) {
}
