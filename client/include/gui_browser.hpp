#pragma once

#include "gui.hpp"

#include <vector>
#include <unordered_map>

typedef struct {
  std::string name;
  enum { FILE, FOLDER, BACK } type;
  u64 fileSize;
} BrowserItem;

class GuiBrowser : public Gui {
public:
  GuiBrowser();
  ~GuiBrowser();

  void update();
  void draw();
  void onInput(u32 kdown);
  void onTouch(touchPosition &touch);
  void onGesture(touchPosition &startPosition, touchPosition &endPosition);

private:
  std::vector<BrowserItem> m_browserItems;
  u16 startIndex;
  u16 currIndex;
  u16 currItemIndex;
  u16 itemsAmount;
};
