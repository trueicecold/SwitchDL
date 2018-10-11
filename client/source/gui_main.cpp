#include "gui_main.hpp"

#include "beta_bin.h"

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

  /*if (Title::g_titles.size() == 0) return;

  if (kdown & KEY_LEFT) {
    if (selectionState == TITLE_SELECT) {
      if (static_cast<s16>(m_selected.titleIndex - 2) >= 0)
        m_selected.titleIndex -= 2;
    } else if (selectionState == ACCOUNT_SELECT) {
      if (static_cast<s16>(m_selected.accountIndex - 1) >= 0)
        m_selected.accountIndex--;
    }
  } else if (kdown & KEY_RIGHT) {
    if (selectionState == TITLE_SELECT) {
      if (static_cast<u16>(m_selected.titleIndex + 2) < ((!m_editableOnly) ?  Title::g_titles.size() : ConfigParser::g_editableTitles.size()))
        m_selected.titleIndex += 2;
    } else if (selectionState == ACCOUNT_SELECT) {
      if (static_cast<u16>(m_selected.accountIndex + 1) < Title::g_titles[m_selected.titleId]->getUserIDs().size())
        m_selected.accountIndex++;
    }
  } else if (kdown & KEY_UP) {
    if (selectionState == TITLE_SELECT) {
      if ((m_selected.titleIndex % 2) == 1) {
          m_selected.titleIndex--;
      }
    }
  } else if (kdown & KEY_DOWN) {
    if (selectionState == TITLE_SELECT) {
      if ((m_selected.titleIndex % 2) == 0) {
        if (static_cast<u16>(m_selected.titleIndex + 1) < ((!m_editableOnly) ?  Title::g_titles.size() : ConfigParser::g_editableTitles.size()))
          m_selected.titleIndex++;
      }
    }
  }

  if (kdown & KEY_A) {
    if (selectionState == TITLE_SELECT)
      selectionState = ACCOUNT_SELECT;
    else if (selectionState == ACCOUNT_SELECT && Title::g_titles[m_selected.titleId]->getUserIDs().size() > 0) {
      Title::g_currTitle = Title::g_titles[m_selected.titleId];
      Account::g_currAccount = Account::g_accounts[Title::g_titles[m_selected.titleId]->getUserIDs()[m_selected.accountIndex]];
      Gui::g_nextGui = GUI_EDITOR;
    }
  }

  if (kdown & KEY_L) {
    m_editableOnly = !m_editableOnly;
    m_selected.titleIndex = 0;
  }

  if (kdown & KEY_X) {
    if (batchClicked) {
      bool batchFailed = false;
      (new MessageBox("Are you sure you want to backup all saves\non this console?\nThis might take a while.", MessageBox::YES_NO))->setSelectionAction([&](s8 selection) {
        if (selection) {
          s16 res;
          time_t t = time(nullptr);
          u16 failed_titles = 0;
          for (auto title : Title::g_titles) {
            for (u128 userID : Title::g_titles[title.first]->getUserIDs()) {
              if((res = backupSave(title.first, userID, true, t))) {
                batchFailed = true;
                failed_titles++;
              }
            }
          }
          if (!batchFailed)
            (new Snackbar("Successfully created backups!"))->show();
          else {
            std::stringstream errorMessage;
            errorMessage << "Failed to backup " << failed_titles << " titles!";
            (new Snackbar(errorMessage.str()))->show();
          }
        }
      })->show();
    }
    else {
      if (selectionState == TITLE_SELECT) {
        bool batchFailed = false;
        s16 res;
        time_t t = time(nullptr);

        for (u128 userID : Title::g_titles[m_selected.titleId]->getUserIDs()) {
          if((res = backupSave(m_selected.titleId, userID, true, t))) {
            batchFailed = true;
          }
        }

        if (!batchFailed)
          (new Snackbar("Successfully created backup!"))->show();
        else (new Snackbar("An error occured while creating the backup! Error " + std::to_string(res)))->show();
      }
    }
  }

  batchClicked = (kdown & KEY_R) > 0;

  if (kdown & KEY_B) {
    if (selectionState == ACCOUNT_SELECT) {
        selectionState = TITLE_SELECT;
        m_selected.accountIndex = 0;
    }
  }
  if (kdown & KEY_MINUS) {
    (new MessageBox("Checking for updates...", MessageBox::NONE))->show();
    GuiMain::g_shouldUpdate = true;
  }*/
}

void GuiMain::onTouch(touchPosition &touch) {
  /*if (Title::g_titles.size() == 0) return;

  switch (selectionState) {
    case TITLE_SELECT: {
      u8 x = floor((touch.px + xOffset) / 256.0F);
      u8 y = floor(touch.py / 256.0F);
      u8 title = y + x * 2;

      if (y <= 1 && title < Title::g_titles.size()) {
        if (m_editableOnly && title > (m_editableCount - 1)) break;
          if (m_selected.titleIndex == title) {
            Title::g_currTitle = Title::g_titles[m_selected.titleId];
            selectionState = ACCOUNT_SELECT;
          }
          m_selected.titleIndex = title;
        }
      break;
    }
    case ACCOUNT_SELECT: {
      u8 account = floor((touch.px - 40) / 150.0F);

      if (account < Title::g_titles[m_selected.titleId]->getUserIDs().size() && touch.py > 560 && touch.py < (560 + 128)) {
        if (m_selected.accountIndex == account) {
          m_selected.userId = Title::g_titles[m_selected.titleId]->getUserIDs()[account];
          Title::g_currTitle = Title::g_titles[m_selected.titleId];
          Account::g_currAccount = Account::g_accounts[Title::g_titles[m_selected.titleId]->getUserIDs()[m_selected.accountIndex]];
          Gui::g_nextGui = GUI_EDITOR;
        }
        m_selected.accountIndex = account;
      } else {
        selectionState = TITLE_SELECT;
        m_selected.accountIndex = 0;
      }

      break;
    }
  }*/
}

void GuiMain::onGesture(touchPosition &startPosition, touchPosition &endPosition) {
  /*if (Title::g_titles.size() == 0) return;*/

}
