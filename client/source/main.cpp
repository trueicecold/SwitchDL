#include <stdio.h>
//#include <switch.h>
#include "gui.hpp"
#include "gui_main.hpp"
#include "gui_settings.hpp"
#include "gui_browser.hpp"
#include "config.hpp"
#include <chrono>

#include <iostream>
#include <math.h>
#include <fstream>
#include <cstdio>
#include <sys/socket.h>
#include <sys/stat.h>
#include <utime.h>
#include <sstream>

#include "threads.hpp"

extern "C" {
  #include "theme.h"
}

#define NXLINK

#define LONG_PRESS_DELAY              2
#define LONG_PRESS_ACTIVATION_DELAY   300

static bool updateThreadRunning = false;

static Mutex mutexCurrGui;
static Gui* currGui = nullptr;
static u32 inputTicker = 0;
static u8 touchCntOld = 0, touchCnt = 0;
static u32 kheld = 0, kheldOld = 0;
static u32 kdown = 0;
static touchPosition touch;
static touchPosition touchEnd;

static u64 repetitionKeys = 0;

void update(void *args) {
  while (updateThreadRunning) {
    auto begin = std::chrono::steady_clock::now();

    mutexLock(&mutexCurrGui);
    if (currGui != nullptr)
      currGui->update();
    mutexUnlock(&mutexCurrGui);

    if (NumericKeyboard::shown) {
      repetitionKeys = (KEY_X);
    }

    if (kheld & repetitionKeys) inputTicker++;
    else inputTicker = 0;

    svcSleepThread(1.0E6 - std::chrono::duration<double, std::nano>(std::chrono::steady_clock::now() - begin).count());
  }
}

void worker(void *args)
{
    /*curlClass myWorker;
    myWorker.initCurl((DownloadInfo*)args);
    myWorker.startCurl();*/
}

int main(int argc, char** argv) {
  socketInitializeDefault();

  #ifdef NXLINK
    nxlinkStdio();
  #endif

  /*std::thread thread1(worker);
  thread1.join();*/

  /*pthread_t t1;
  pthread_create(&t1, NULL, &worker, NULL);*/

  gfxInitDefault();

  setsysInitialize();
  ColorSetId colorSetId;
  setsysGetColorSetId(&colorSetId);
  setTheme(colorSetId);
  setsysExit();

  Config::load();
  Gui::g_nextGui = GUI_BROWSER;

  /*Handle txHandle;
  if (R_FAILED(smRegisterService(&txHandle, "tx", false, 1)))
    Gui::g_nextGui = GUI_TX_WARNING;
  else {
    Gui::g_nextGui = GUI_MAIN;
    smUnregisterService("tx");
  }*/

  mutexInit(&mutexCurrGui);

  updateThreadRunning = true;

  /*for(u32 i = 0; i < 5; i++) {
    DownloadInfo *dlInfo = new DownloadInfo();
    dlInfo->start = (1024ULL * 1024ULL * 10 * 0);
    dlInfo->end = (1024ULL * 1024ULL * 10 * (4 + 1) - 1);
    dlInfo->index = i + 1;

    Threads::create(&worker, dlInfo);
  }*/

  Threads::create(&update, nullptr);

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
        case GUI_SETTINGS:
          currGui = new GuiSettings();
          repetitionKeys = 0;
          break;
        case GUI_BROWSER:
          currGui = new GuiBrowser();
          repetitionKeys = (KEY_UP | KEY_DOWN);
          break;
        default: 
          repetitionKeys = 0;
          break;
      }
      Gui::g_nextGui = GUI_INVALID;
      mutexUnlock(&mutexCurrGui);
    }

    if (currGui != nullptr) {
      currGui->draw();

      if (kdown & KEY_PLUS) {
        if (!NumericKeyboard::shown) {
          break;
        }
      }

      if (kdown || hidKeysUp(CONTROLLER_P1_AUTO)) {
        if (NumericKeyboard::shown) {
          NumericKeyboard::onInput(kdown);
        }
        else {
          currGui->onInput(kdown);
        }
      }

      if (inputTicker > LONG_PRESS_ACTIVATION_DELAY && (inputTicker % LONG_PRESS_DELAY) == 0) {
        if (NumericKeyboard::shown) {
          NumericKeyboard::onInput(kheld);
        }
        else {
          currGui->onInput(kheld);
        }
      }
    }

    touchCnt = hidTouchCount();

    if (touchCnt > touchCntOld)
      hidTouchRead(&touch, 0);

    if (touchCnt < touchCntOld) {
      if (NumericKeyboard::shown) {
          NumericKeyboard::onTouch(touchEnd);
          //NumericKeyboard::onGesture(touch, touchEnd);
      }
      else {
        currGui->onTouch(touchEnd);
        currGui->onGesture(touch, touchEnd);
      }
    }

    hidTouchRead(&touchEnd, 0);

    touchCntOld = touchCnt;

    if (kheld != kheldOld)
      inputTicker = 0;

    kheldOld = kheld;
  }

  /*curlClass::downloadCanceled = true;*/
  updateThreadRunning = false;
  Threads::joinAll();

  delete currGui;
  socketExit();
  gfxExit();
  return 0;
}
