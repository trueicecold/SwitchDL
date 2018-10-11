#include <stdio.h>
//#include <switch.h>
#include "gui.hpp"
#include "gui_main.hpp"
#include <chrono>

#include "threads.hpp"

extern "C" {
  #include "theme.h"
}

#define NXLINK

#define LONG_PRESS_DELAY              2
#define LONG_PRESS_ACTIVATION_DELAY   300

static bool updateThreadRunning = false;
static u32 inputTicker = 0;

static Mutex mutexCurrGui;
static Gui* currGui = nullptr;
static u32 kdown = 0;
static u32 kheld = 0;


void update(void *args) {
  while (updateThreadRunning) {
    auto begin = std::chrono::steady_clock::now();

    mutexLock(&mutexCurrGui);
    if (currGui != nullptr)
      currGui->update();
    mutexUnlock(&mutexCurrGui);

    if (kheld & (KEY_LEFT | KEY_RIGHT | KEY_UP | KEY_DOWN)) inputTicker++;
    else inputTicker = 0;

    svcSleepThread(1.0E6 - std::chrono::duration<double, std::nano>(std::chrono::steady_clock::now() - begin).count());
  }
}

int main(int argc, char** argv) {
  socketInitializeDefault();

  #ifdef NXLINK
    nxlinkStdio();
  #endif

  gfxInitDefault();

  setsysInitialize();
  ColorSetId colorSetId;
  setsysGetColorSetId(&colorSetId);
  setTheme(colorSetId);
  setsysExit();

  Gui::g_nextGui = GUI_MAIN;

  /*Handle txHandle;
  if (R_FAILED(smRegisterService(&txHandle, "tx", false, 1)))
    Gui::g_nextGui = GUI_TX_WARNING;
  else {
    Gui::g_nextGui = GUI_MAIN;
    smUnregisterService("tx");
  }*/

  mutexInit(&mutexCurrGui);

  updateThreadRunning = true;
  Threads::create(&update);

  while (appletMainLoop()) {
    hidScanInput();
    kheld = hidKeysHeld(CONTROLLER_P1_AUTO);
    kdown = hidKeysDown(CONTROLLER_P1_AUTO);

    if (Gui::g_nextGui != GUI_INVALID) {
      mutexLock(&mutexCurrGui);
      if (currGui != nullptr)
        delete currGui;

      switch (Gui::g_nextGui) {
        case GUI_MAIN:
          currGui = new GuiMain();
          break;
        default: break;
      }
      Gui::g_nextGui = GUI_INVALID;
      mutexUnlock(&mutexCurrGui);
    }

    if (currGui != nullptr) {
      currGui->draw();
    }

    if (kdown & KEY_PLUS)
      break;
  }

  updateThreadRunning = false;
  Threads::joinAll();

  socketExit();
  gfxExit();
  return 0;
}
