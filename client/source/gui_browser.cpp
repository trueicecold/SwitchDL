#include "gui_browser.hpp"
#include "file_downloader.hpp"

#include <sstream>

#include <string>
#include <sstream>
#include <math.h>

#include "json.hpp"
using json = nlohmann::json;

GuiBrowser::GuiBrowser() : Gui() {
}

GuiBrowser::~GuiBrowser() {
}

void GuiBrowser::update() {
  Gui::update();
}

void GuiBrowser::draw() {
  Gui::beginDraw();
  Gui::drawRectangle(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColor);

  u16 index = 0;
  for(auto item : m_browserItems) {
    std::stringstream ss;
    ss << item.fileSize << " kB  ";
    Gui::drawRectangle(0, 80 * index + 50, Gui::g_framebuffer_width, 75, currTheme.selectedButtonColor);
    Gui::drawTextAligned(font20, 80, 80 * index + 70, currTheme.textColor, item.name.c_str(), ALIGNED_LEFT);
    Gui::drawTextAligned(font20, Gui::g_framebuffer_width, 80 * index + 70, currTheme.textColor, ss.str().c_str(), ALIGNED_RIGHT);

    index++;
  }

  Gui::endDraw();
}

void GuiBrowser::onInput(u32 kdown) {

  if (kdown & KEY_LEFT) {
  } else if (kdown & KEY_RIGHT) {
  } else if (kdown & KEY_UP) {
  } else if (kdown & KEY_DOWN) {
  }

  if (kdown & KEY_A) {
    FileDownloader downloader;

    json j;

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

  if (kdown & KEY_L) {
  }

  if (kdown & KEY_X) {
  }

  if (kdown & KEY_B) {
  }

  if (kdown & KEY_MINUS) {
  }
}

void GuiBrowser::onTouch(touchPosition &touch) {
}

void GuiBrowser::onGesture(touchPosition &startPosition, touchPosition &endPosition) {
  /*if (Title::g_titles.size() == 0) return;*/

}
