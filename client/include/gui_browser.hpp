#pragma once

#include "gui.hpp"

#include <vector>
#include <unordered_map>
#include <string>
#include <threads.h>

#include "worker.hpp"

typedef struct {
  std::string name;
  enum { FILE, FOLDER, BACK } type;
  u64 fileSize;
} BrowserItem;

enum ConnectionState {
  NO_CONFIG,
  NOT_CONNECTED,
  CONNECTION_ERROR,
  LOADING,
  LOADED
};

class GuiBrowser : public Gui {
public:
  GuiBrowser();
  ~GuiBrowser();

  void update();
  void draw();
  void getFileList();
  void getFileListThread();
  void getFileListThreadResponse(std::string response);
  void getFileListResponse(std::string response);
  void onInput(u32 kdown);
  void onTouch(touchPosition &touch);
  void onGesture(touchPosition &startPosition, touchPosition &endPosition);

private:
  static inline ConnectionState connectionState;
  std::string folderPath = "";
  std::string backFolderPath = "";
  std::vector<BrowserItem> m_browserItems;
  u16 yOffset;
  u16 startIndex;
  u16 currIndex;
  BrowserItem currItem;
  u16 itemsAmount;

  thrd_t fileListThread; 
  int fileListResult;
};
