#include "numeric_keyboard.hpp"
#include "gui.hpp"
#include <vector>

typedef struct {
   s32 x, y, w, h; 
   std::string c;
} Button;

/*static void NumericKeyboard::onGesture(touchPosition &startPosition, touchPosition &endPosition) {
}*/

std::vector<Button> buttons {
    {
        .x = 360,
        .y = 390,
        .w = 184,
        .h = 60,
        .c = "1"
    },
    {
        .x = 549,
        .y = 390,
        .w = 184,
        .h = 60,
        .c = "2"
    },
    {
        .x = 738,
        .y = 390,
        .w = 184,
        .h = 60,
        .c = "3"
    },
    {
        .x = 360,
        .y = 454,
        .w = 184,
        .h = 60,
        .c = "4"
    },
    {
        .x = 549,
        .y = 454,
        .w = 184,
        .h = 60,
        .c = "5"
    },
    {
        .x = 738,
        .y = 454,
        .w = 184,
        .h = 60,
        .c = "6"
    },
    {
        .x = 360,
        .y = 518,
        .w = 184,
        .h = 60,
        .c = "7"
    },
    {
        .x = 549,
        .y = 518,
        .w = 184,
        .h = 60,
        .c = "8"
    },
    {
        .x = 738,
        .y = 518,
        .w = 184,
        .h = 60,
        .c = "9"
    },
    {
        .x = 360,
        .y = 582,
        .w = 184,
        .h = 60,
        .c = "."
    },
    {
        .x = 549,
        .y = 582,
        .w = 184,
        .h = 60,
        .c = "0"
    }
};

NumericKeyboard::NumericKeyboard()
{
    setsysInitialize();
    setsysGetColorSetId(&NumericKeyboard::colorSetId);
    setsysExit();
}

NumericKeyboard::~NumericKeyboard()
{
}

void NumericKeyboard::show(std::string caption) {
    NumericKeyboard::edit_display_string = std::string(*NumericKeyboard::bind_value);
    NumericKeyboard::caption_display_string = std::string(caption   );
    NumericKeyboard::shown = true;
}

void NumericKeyboard::hide() {
    NumericKeyboard::shown = false;
    NumericKeyboard::bind_value = nullptr;
    NumericKeyboard::edit_display_string = "";
}

void NumericKeyboard::onTouch(touchPosition &touch) {
    for ( Button &button : buttons ) {
        if (touch.px >= button.x && touch.px <= button.x+button.w && touch.py >= button.y && touch.py <= button.y+button.h) {
            if (button.c != "\uE149")
                NumericKeyboard::edit_display_string += button.c;
            return;
        }
    }
    if (touch.px >= 927 && touch.px <= 1043 && touch.py >= 390 && touch.py <= 450) {
        NumericKeyboard::edit_display_string.pop_back();
        return;
    }
    if (touch.px >= 927 && touch.px <= 1043 && touch.py >= 454 && touch.py <= 644) {
        *NumericKeyboard::bind_value = std::string(NumericKeyboard::edit_display_string);
        NumericKeyboard::hide();
    }
}

void NumericKeyboard::draw(Gui *gui) {
    u32 glyphWidth,glyphHeight;

    //drawing Keyboard UI
    gui->drawRectangled(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height-350, currTheme.backgroundColorSemi);
    gui->drawRectangle(0, Gui::g_framebuffer_height-350, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.keyboardBackgroundColor);
    gui->drawRectangle(390, 245, 600, 5, currTheme.textColor);

    //Drawing caption
    gui->drawText(font24, 130, 55, currTheme.textColor, NumericKeyboard::caption_display_string.c_str());
    
    //Drawing edited value
    gui->drawText(font24, 405, 200, currTheme.textColor, NumericKeyboard::edit_display_string.c_str());

    //Drawing numeric buttons
    for ( Button &button : buttons ) {
        gui->getTextDimensions(font24, button.c.c_str(), &glyphWidth, &glyphHeight);
        gui->drawRectangle(button.x, button.y, button.w, button.h, currTheme.keyboardButtonBackgroundColor);
        gui->drawText(font24, button.x+((button.w-glyphWidth)/2), button.y+6, currTheme.textColor, button.c.c_str());
    }

    //Drawing delete and OK buttons
    gui->getTextDimensions(font24, "\u3e91", &glyphWidth, &glyphHeight);
    gui->drawRectangle(927, 390, 116, 60, currTheme.keyboardDeleteBackgroundColor);
    gui->drawText(font24, 927 + ((116-glyphWidth)/2), 393, currTheme.keyboardDeleteTextColor, "\ue091");
    gui->drawText(font20, 1016, 387, currTheme.keyboardDeleteTextColor, "\ue0e1");

    gui->getTextDimensions(font24, "OK", &glyphWidth, &glyphHeight);
    gui->drawRectangle(927, 454, 116, 190, currTheme.keyboardOKBackgroundColor);
    gui->drawText(font24, 927 + ((116-glyphWidth)/2), 524, currTheme.keyboardDeleteTextColor, "OK");
    gui->drawText(font20, 1016, 451, currTheme.keyboardDeleteTextColor, "\ue0ef");
}