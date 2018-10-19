#include "gui_browser.hpp"
#include "file_downloader.hpp"

#include <sstream>

#include <string>
#include <sstream>
#include <math.h>

#include "json.hpp"
using json = nlohmann::json;

GuiBrowser::GuiBrowser() : Gui() {
  FileDownloader downloader;

  startIndex = 0;
  currIndex = 0;
  currItemIndex = 0;
  itemsAmount = 7;

  json j;

  try {
    if (downloader.ping() == "pong") {
      try {
        j = json::parse(downloader.getFileList());
      } catch (json::parse_error& e) {
        printf("JSON parse error!\n");
      }

      if(j == nullptr) return;

      for(auto item : j["items"]) {
        if(item["type"] == "file")
          m_browserItems.push_back({ item["name"], BrowserItem::FILE, item["size"] });
        else
          m_browserItems.push_back({ item["name"].get<std::string>() + std::string(" (Folder)"), BrowserItem::FOLDER, 0 });
      }
    }
    else {
      printf("Failed pinging server!\n");
    }
  }
  catch(std::exception& e) {
    printf("Error loading server contents!\n");
  }
}

GuiBrowser::~GuiBrowser() {
}

void GuiBrowser::update() {
  Gui::update();
}

void GuiBrowser::draw() {
  Gui::beginDraw();
  Gui::drawRectangle(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColor);

  u16 drawIndex = 0;
  for(auto item : m_browserItems) {
    if (drawIndex >= startIndex && drawIndex < startIndex+itemsAmount) {
      std::stringstream ss;
      ss << item.fileSize << " kB  ";
      if (currIndex == drawIndex)
        Gui::drawRectangle(4, 80 * (drawIndex-startIndex) + 50 - 4, Gui::g_framebuffer_width-8, 83, currTheme.highlightColor);
      Gui::drawRectangle(8, 80 * (drawIndex-startIndex) + 50, Gui::g_framebuffer_width-16, 75, currTheme.selectedButtonColor);
      Gui::drawTextAligned(font20, 80, 80 * (drawIndex-startIndex) + 70, currTheme.textColor, item.name.c_str(), ALIGNED_LEFT);
      Gui::drawTextAligned(font20, Gui::g_framebuffer_width, 80 * (drawIndex-startIndex) + 70, currTheme.textColor, ss.str().c_str(), ALIGNED_RIGHT);
    }
    drawIndex++;
  }

  Gui::endDraw();
}

void GuiBrowser::onInput(u32 kdown) {
  if (kdown & KEY_UP) {
    if (currIndex > 0) {
      currIndex--;
      if (currIndex < startIndex+3 && startIndex > 0) {
        startIndex--;
      }
    }

  } else if (kdown & KEY_DOWN) {
    if (currIndex < m_browserItems.size()-1) {
      currIndex++;
      if (currIndex > startIndex+itemsAmount-4 && startIndex < m_browserItems.size()) {
        startIndex++;
      }
    }
  }
  printf("%d, %d\n", currIndex, startIndex);
  
  
  
  
  if (kdown & KEY_A) {
  }

  if (kdown & KEY_L) {
  }

  if (kdown & KEY_X) {
  }

  if (kdown & KEY_B) {
  }

  if (kdown & KEY_MINUS) {
    Gui::g_nextGui = GUI_SETTINGS;
  }
}

void GuiBrowser::onTouch(touchPosition &touch) {
}

void GuiBrowser::onGesture(touchPosition &startPosition, touchPosition &endPosition) {
  /*if (Title::g_titles.size() == 0) return;*/

}
