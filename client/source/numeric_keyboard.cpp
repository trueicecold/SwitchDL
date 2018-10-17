#include "numeric_keyboard.hpp"
#include "gui.hpp"
#include <vector>

typedef struct {
   s32 x, y, w, h; 
   std::string c;
} Button;

NumericKeyboard::NumericKeyboard()
{
}

NumericKeyboard::~NumericKeyboard()
{
}

void NumericKeyboard::show() {
    NumericKeyboard::display_string = std::string(*NumericKeyboard::bind_value);
    NumericKeyboard::shown = true;
}

void NumericKeyboard::hide() {
}

std::vector<Button> buttons {
    {
        .x = 435,
        .y = 460,
        .w = 100,
        .h = 50,
        .c = "1"
    },
    {
        .x = 545,
        .y = 460,
        .w = 100,
        .h = 50,
        .c = "2"
    },
    {
        .x = 655,
        .y = 460,
        .w = 100,
        .h = 50,
        .c = "3"
    },
    {
        .x = 435,
        .y = 520,
        .w = 100,
        .h = 50,
        .c = "4"
    },
    {
        .x = 545,
        .y = 520,
        .w = 100,
        .h = 50,
        .c = "5"
    },
    {
        .x = 655,
        .y = 520,
        .w = 100,
        .h = 50,
        .c = "6"
    },
    {
        .x = 435,
        .y = 580,
        .w = 100,
        .h = 50,
        .c = "7"
    },
    {
        .x = 545,
        .y = 580,
        .w = 100,
        .h = 50,
        .c = "8"
    },
    {
        .x = 655,
        .y = 580,
        .w = 100,
        .h = 50,
        .c = "9"
    },
    {
        .x = 435,
        .y = 640,
        .w = 100,
        .h = 50,
        .c = "."
    },
    {
        .x = 545,
        .y = 640,
        .w = 100,
        .h = 50,
        .c = "0"
    },
    {
        .x = 655,
        .y = 640,
        .w = 100,
        .h = 50,
        .c = "\uE149"
    }
};

void NumericKeyboard::draw(Gui *gui) {
    u32 glyphWidth,glyphHeight;

    gui->drawRectangled(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColorSemi);
    
    gui->drawText(font20, 427, 422, currTheme.textColor, NumericKeyboard::display_string.c_str());

    gui->drawRectangle(427, 452, 336, 246, currTheme.keyboardBackgroundColor);
    for ( Button &button : buttons ) {
        gui->getTextDimensions(font24, button.c.c_str(), &glyphWidth, &glyphHeight);
        gui->drawRectangle(button.x, button.y, button.w, button.h, currTheme.keyboardButtonBackgroundColor);
        gui->drawText(font24, button.x+((button.w-glyphWidth)/2), button.y+3, currTheme.textColor, button.c.c_str());
    }
}