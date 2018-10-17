#pragma once

#include <curl/curl.h>
#include <stdio.h>
#include <fstream>
#include <cstdio>
#include <math.h>
#include <sstream>
#include <iostream>
#include <sys/stat.h>

extern "C" {
  #include "types.h"
}

typedef struct {
  u64 start, end;
  u32 index;
} DownloadInfo;

class FileDownloader
{
  private:
    CURL * curl {};
    CURLcode res;
    FILE* fp;
    u32 currIndex;

  public:
    void initDownload(DownloadInfo *dlInfo);
    void startDownload();
    static int calcProgress(void* ptr, double TotalToDownload, double NowDownloaded, double TotalToUpload, double NowUploaded);
    static std::string formatBytes(uint bytes);
    static size_t writeToFile(void *ptr, size_t size, size_t nmemb, FILE *stream);
    static inline bool downloadCanceled = false;
    static inline u32 index = 0;
    static inline u32 downloaded[5];

    FileDownloader();
    ~FileDownloader();
};