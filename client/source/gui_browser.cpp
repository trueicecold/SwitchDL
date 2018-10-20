#include "gui_browser.hpp"
#include "file_downloader.hpp"
#include "config.hpp"

#include <sstream>

#include <string>
#include <sstream>
#include <math.h>

#include "json.hpp"

using json = nlohmann::json;

GuiBrowser::GuiBrowser() : Gui() {
  FileDownloader downloader;

  yOffset = 87;
  startIndex = 0;
  currIndex = 0;
  itemsAmount = 7;
  connectionState = ConnectionState::NOT_CONNECTED;
  
  ping();
}

GuiBrowser::~GuiBrowser() {
}

void GuiBrowser::update() {
  Gui::update();
}

void GuiBrowser::draw() {
  Gui::beginDraw();
  Gui::drawRectangle(0, 0, Gui::g_framebuffer_width, Gui::g_framebuffer_height, currTheme.backgroundColor);

  switch (connectionState) {
    case ConnectionState::NOT_CONNECTED:
      Gui::drawTextAligned(font20, Gui::g_framebuffer_width/2, Gui::g_framebuffer_height/2, currTheme.textColor, "Not connected to server.", ALIGNED_CENTER);
      break;
    case ConnectionState::CONNECTION_ERROR:
      Gui::drawTextAligned(font20, Gui::g_framebuffer_width/2, Gui::g_framebuffer_height/2, currTheme.textColor, "Error connecting to server. Please check the IP and Port and try again.", ALIGNED_CENTER);
      break;
    case ConnectionState::LOADING:
      Gui::drawTextAligned(font20, Gui::g_framebuffer_width/2, Gui::g_framebuffer_height/2, currTheme.textColor, "Loading file list...", ALIGNED_CENTER);
      break;
    case ConnectionState::LOADED:
      u16 drawIndex = 0;
      for(auto item : m_browserItems) {
        if (drawIndex >= startIndex && drawIndex < startIndex+itemsAmount) {
          std::stringstream ss;
          ss << item.fileSize << " kB  ";
          if (currIndex == drawIndex)
            Gui::drawRectangle(4, 80 * (drawIndex-startIndex) + yOffset - 4, Gui::g_framebuffer_width-8, 83, currTheme.highlightColor);
          Gui::drawRectangle(8, 80 * (drawIndex-startIndex) + yOffset, Gui::g_framebuffer_width-16, 75, currTheme.selectedButtonColor);
          if (item.type == BrowserItem::FOLDER)
            Gui::drawTextAligned(font20, 80, 80 * (drawIndex-startIndex) + yOffset + 20, currTheme.textColor, (item.name + " (Folder)").c_str(), ALIGNED_LEFT);
          else if (item.type == BrowserItem::FILE) {
            Gui::drawTextAligned(font20, 80, 80 * (drawIndex-startIndex) + yOffset + 20, currTheme.textColor, item.name.c_str(), ALIGNED_LEFT);
            Gui::drawTextAligned(font20, Gui::g_framebuffer_width, 80 * (drawIndex-startIndex) + yOffset + 20, currTheme.textColor, ss.str().c_str(), ALIGNED_RIGHT);
          }
          else
            Gui::drawTextAligned(font20, 80, 80 * (drawIndex-startIndex) + yOffset + 20, currTheme.textColor, item.name.c_str(), ALIGNED_LEFT);
        }
        drawIndex++;

        //Drawing the top part
        Gui::drawRectangle(0, 0, Gui::g_framebuffer_width, 65, currTheme.keyboardBackgroundColor);
        Gui::drawText(font20, 24, 19, currTheme.textColor, ("Currently browsing: " + folderPath).c_str());

        //Drawing the bottom part
        Gui::drawRectangle(30, 658, 1220, 1, currTheme.textColor);
        Gui::drawTextAligned(font20, 50, Gui::g_framebuffer_height - 50, currTheme.textColor, "\uE0E4 Page up     \uE0E5 Page down", ALIGNED_LEFT);
        switch (currItem.type) {
          case BrowserItem::FOLDER:
            Gui::drawTextAligned(font20, Gui::g_framebuffer_width - 50, Gui::g_framebuffer_height - 50, currTheme.textColor, "\uE0E0 Enter folder     \uE0EF Exit", ALIGNED_RIGHT);
            break;
          case BrowserItem::FILE:
            Gui::drawTextAligned(font20, Gui::g_framebuffer_width - 50, Gui::g_framebuffer_height - 50, currTheme.textColor, "\uE0E0 Download file     \uE0EF Exit", ALIGNED_RIGHT);
            break;
          case BrowserItem::BACK:
            Gui::drawTextAligned(font20, Gui::g_framebuffer_width - 50, Gui::g_framebuffer_height - 50, currTheme.textColor, "\uE0E0 Up a level     \uE0EF Exit", ALIGNED_RIGHT);
            break;
        }
      }
      break;
  }

  Gui::endDraw();
}

void GuiBrowser::ping() {
  printf("ping\f");
  FileDownloader downloader;

  if (downloader.ping() == "pong") {
    getFileList();
  }
  else {
    connectionState = ConnectionState::CONNECTION_ERROR;
  }
}

void GuiBrowser::getFileList() {
  json listJson;
  FileDownloader downloader;
  m_browserItems.clear();

  currIndex = 0;
  startIndex = 0;

  connectionState = ConnectionState::LOADING;

  try {
    listJson = json::parse(downloader.getFileList(folderPath));
    if(listJson == nullptr) return;
    
    folderPath = listJson["path"];
    backFolderPath = listJson["backPath"];

    if (folderPath != "/") m_browserItems.push_back({ "..", BrowserItem::BACK, 0 });
    for(auto item : listJson["items"]) {
      if(item["type"] == "file")
        m_browserItems.push_back({ item["name"], BrowserItem::FILE, item["size"] });
      else
        m_browserItems.push_back({ item["name"].get<std::string>(), BrowserItem::FOLDER, 0 });
    }
    if (m_browserItems.size() > 0)
      currItem = m_browserItems[0];
    connectionState = ConnectionState::LOADED;
  }
  catch(std::exception& e) {
    connectionState = ConnectionState::CONNECTION_ERROR;
  }
}

void GuiBrowser::onInput(u32 kdown) {
  if (kdown & KEY_UP) {
    if (currIndex > 0) {
      currIndex--;
      currItem = m_browserItems[currIndex];
      if (currIndex < startIndex+3 && startIndex > 0) {
        startIndex--;
      }
    }

  } else if (kdown & KEY_DOWN) {
    if (currIndex < m_browserItems.size()-1) {
      currIndex++;
      currItem = m_browserItems[currIndex];
      if (currIndex > startIndex+itemsAmount-4 && startIndex < m_browserItems.size()) {
        startIndex++;
      }
    }
  }
  else if (kdown & KEY_A) {
    if (currItem.type == BrowserItem::FOLDER) {
      folderPath += std::string("/" + currItem.name);
      getFileList();
    }
    else if (currItem.type == BrowserItem::BACK) {
      folderPath = backFolderPath;
      getFileList();
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
