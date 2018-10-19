#include "gui_settings.hpp"
#include "file_downloader.hpp"

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

FileDownloader downloader;

void GuiSettings::draw() {
    Gui::beginDraw();
    Gui::drawRectangle(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColor);
    Gui::drawText(font24, 50, 50, currTheme.textColor, "SwitchDL Settings");
    Gui::drawRectangle(50, 90, 260, 2, currTheme.textColor);

    Gui::drawText(font24, 50, 160, currTheme.textColor, "IP Address:");
    Gui::drawBorderedRectangle(250, 166, 350, 40, 1, currTheme.keyboardOKBackgroundColor, currTheme.backgroundColor);
    Gui::drawText(font20, 255, 170, currTheme.keyboardOKBackgroundColor, ip_address.c_str());

    Gui::drawText(font24, 50, 219, currTheme.textColor, "Port:");
    Gui::drawBorderedRectangle(250, 225, 200, 40, 1, currTheme.keyboardOKBackgroundColor, currTheme.backgroundColor);
    Gui::drawText(font20, 255, 229, currTheme.keyboardOKBackgroundColor, port.c_str());

    Gui::drawTextAligned(font20, Gui::g_framebuffer_width - 50, Gui::g_framebuffer_height - 50, currTheme.textColor, "\uE0E1 Back     \uE0E0 Save", ALIGNED_RIGHT);
    Gui::endDraw();
}

void GuiSettings::onInput(u32 kdown) {
    if (!NumericKeyboard::shown) {
        if (kdown & KEY_B) {
            Gui::g_nextGui = GUI_BROWSER;
        }
    }
}

void GuiSettings::onTouch(touchPosition &touch) {
    if (touch.px >= 250 && touch.px <= 600 && touch.py >= 166 && touch.py <= 206) {
        NumericKeyboard::bind_value = &ip_address;
        NumericKeyboard::show("Enter the IP address.");
    }
    else if (touch.px >= 250 && touch.px <= 450 && touch.py >= 225 && touch.py <= 265) {
        NumericKeyboard::bind_value = &port;
        NumericKeyboard::show("Enter the port number.");
    }
}

void GuiSettings::onGesture(touchPosition &startPosition, touchPosition &endPosition) {
}
