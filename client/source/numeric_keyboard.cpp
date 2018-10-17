#include "numeric_keyboard.hpp"
#include "gui.hpp"

NumericKeyboard::NumericKeyboard()
{
}

NumericKeyboard::~NumericKeyboard()
{
}

void NumericKeyboard::show(u32 startX, u32 startY) {
    _startX = startX;
    _startY = startY;
    NumericKeyboard::shown = true;
}

void NumericKeyboard::hide() {
}

void NumericKeyboard::draw(Gui *gui) {
    u32 glyphWidth,glyphHeight;

    gui->drawRectangled(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColorSemi);

    gui->drawRectangled(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColorSemi);
    
    gui->getTextDimensions(font24, "1", &glyphWidth, &glyphHeight);
    gui->drawRectangle(_startX, _startY, 100, 55, currTheme.selectedColor);
    gui->drawText(font24, _startX+((100-glyphWidth)/2), _startY+3, currTheme.textColor, "1");

    gui->getTextDimensions(font24, "2", &glyphWidth, &glyphHeight);
    gui->drawRectangle(_startX+110, _startY, 100, 55, currTheme.selectedColor);
    gui->drawText(font24, _startX+110+((100-glyphWidth)/2), _startY+3, currTheme.textColor, "2");

    gui->getTextDimensions(font24, "3", &glyphWidth, &glyphHeight);
    gui->drawRectangle(_startX+220, _startY, 100, 55, currTheme.selectedColor);
    gui->drawText(font24, _startX+220+((100-glyphWidth)/2), _startY+3, currTheme.textColor, "3");

    gui->getTextDimensions(font24, "4", &glyphWidth, &glyphHeight);
    gui->drawRectangle(_startX, _startY+65, 100, 55, currTheme.selectedColor);
    gui->drawText(font24, _startX+((100-glyphWidth)/2), _startY+65+3, currTheme.textColor, "4");

    gui->getTextDimensions(font24, "5", &glyphWidth, &glyphHeight);
    gui->drawRectangle(_startX+110, _startY+65, 100, 55, currTheme.selectedColor);
    gui->drawText(font24, _startX+110+((100-glyphWidth)/2), _startY+65+3, currTheme.textColor, "5");

    gui->getTextDimensions(font24, "6", &glyphWidth, &glyphHeight);
    gui->drawRectangle(_startX+220, _startY+65, 100, 55, currTheme.selectedColor);
    gui->drawText(font24, _startX+220+((100-glyphWidth)/2), _startY+65+3, currTheme.textColor, "6");    

    gui->getTextDimensions(font24, "7", &glyphWidth, &glyphHeight);
    gui->drawRectangle(_startX, _startY+130, 100, 55, currTheme.selectedColor);
    gui->drawText(font24, _startX+((100-glyphWidth)/2), _startY+130+3, currTheme.textColor, "7");

    gui->getTextDimensions(font24, "8", &glyphWidth, &glyphHeight);
    gui->drawRectangle(_startX+110, _startY+130, 100, 55, currTheme.selectedColor);
    gui->drawText(font24, _startX+110+((100-glyphWidth)/2), _startY+130+3, currTheme.textColor, "8");

    gui->getTextDimensions(font24, "9", &glyphWidth, &glyphHeight);
    gui->drawRectangle(_startX+220, _startY+130, 100, 55, currTheme.selectedColor);
    gui->drawText(font24, _startX+220+((100-glyphWidth)/2), _startY+130+3, currTheme.textColor, "9");  

    gui->getTextDimensions(font24, ".", &glyphWidth, &glyphHeight);
    gui->drawRectangle(_startX, _startY+195, 100, 55, currTheme.selectedColor);
    gui->drawText(font24, _startX+((100-glyphWidth)/2), _startY+195+3, currTheme.textColor, ".");

    gui->getTextDimensions(font24, "0", &glyphWidth, &glyphHeight);
    gui->drawRectangle(_startX+110, _startY+195, 100, 55, currTheme.selectedColor);
    gui->drawText(font24, _startX+110+((100-glyphWidth)/2), _startY+195+3, currTheme.textColor, "0");

    gui->getTextDimensions(font24, "\uE149", &glyphWidth, &glyphHeight);
    gui->drawRectangle(_startX+220, _startY+195, 100, 55, currTheme.selectedColor);
    gui->drawText(font24, _startX+220+((100-glyphWidth)/2), _startY+195+3, currTheme.textColor, "\uE149");      

    /*gui->drawRectangled(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColorSemi);
    gui->drawRectangled(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColorSemi);
    gui->drawRectangled(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColorSemi);
    gui->drawRectangled(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColorSemi);
    gui->drawRectangled(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColorSemi);
    gui->drawRectangled(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColorSemi);
    gui->drawRectangled(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColorSemi);
    gui->drawRectangled(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColorSemi);
    gui->drawRectangled(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColorSemi);
    gui->drawRectangled(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColorSemi);*/

}