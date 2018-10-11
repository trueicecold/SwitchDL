#include <stdio.h>
//#include <switch.h>
#include "gui.hpp"
#include "gui_main.hpp"
#include <chrono>
#include <curl/curl.h>

#include <iostream>
#include <math.h>
#include <fstream>
#include <cstdio>
#include <sys/socket.h>
#include <sys/stat.h>
#include <utime.h>

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

CURL *curl;

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

std::string pretty_bytes(uint bytes)
{
    const char* suffixes[7];
    suffixes[0] = "B";
    suffixes[1] = "KB";
    suffixes[2] = "MB";
    suffixes[3] = "GB";
    suffixes[4] = "TB";
    suffixes[5] = "PB";
    suffixes[6] = "EB";
    uint s = 0; // which suffix to use
    double count = bytes;
    while (count >= 1024 && s < 7)
    {
        s++;
        count /= 1024;
    }
    return std::to_string(count) + " " + suffixes[s];
}

int progress_func(void* ptr, double TotalToDownload, double NowDownloaded, 
                    double TotalToUpload, double NowUploaded)
{
    // ensure that the file to be downloaded is not empty
    // because that would cause a division by zero error later on
    if (TotalToDownload <= 0.0) {
        return 0;
    }

    // how wide you want the progress meter to be
    int totaldotz=40;
    double fractiondownloaded = NowDownloaded / TotalToDownload;
    // part of the progressmeter that's already "full"
    int dotz = round(fractiondownloaded * totaldotz);

    // create the "meter"
    int ii=0;
    printf("%s [",(pretty_bytes(NowDownloaded).c_str()));
    // part  that's full already
    for ( ; ii < dotz;ii++) {
        printf("=");
    }
    // remaining part (spaces)
    for ( ; ii < totaldotz;ii++) {
        printf(" ");
    }
    // and back to line begin - do not forget the fflush to avoid output buffering problems!
    printf("]\r");
    fflush(stdout);
    // if you don't return 0, the transfer will be aborted - see the documentation
    return 0; 
}

size_t writeToFile(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int main(int argc, char** argv) {
  socketInitializeDefault();

  #ifdef NXLINK
    nxlinkStdio();
  #endif

  /********************/
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();

  if (!curl)
    printf("Curl initialization failed!\n");

  mkdir("/SwitchDL", 0777);

  std::string file_path = "/SwitchDL/file.nsp";

  FILE* fp;
  fp = fopen(file_path.c_str(), "wb");

  curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.1.104:3000/static/SMPNO.nsp");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToFile);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);    
  curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
  curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, progress_func); 


  CURLcode res = curl_easy_perform(curl);

  if (res != CURLE_OK)
    printf("Update download CURL perform failed: %s\n", curl_easy_strerror(res));

  fclose(fp); 
  /*********************/

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
    printf("asdsadsad\n");
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
