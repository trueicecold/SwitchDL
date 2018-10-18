#include "file_downloader.hpp"

FileDownloader::FileDownloader()
{
  downloadCanceled = false;
  curl_global_init(CURL_GLOBAL_DEFAULT);
}

FileDownloader::~FileDownloader()
{
}

std::string FileDownloader::getFileList() {
  std::string buffer;
  curl = curl_easy_init();
  if (!curl)
    printf("Curl initialization failed!\n");

  curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.1.140:3333/list");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToString);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

  CURLcode res = curl_easy_perform(curl);

  if (res != CURLE_OK)
    printf("Update download CURL perform failed: %s\n", curl_easy_strerror(res));

  curl_easy_cleanup(curl);

  return buffer;
}

std::string FileDownloader::ping() {
  std::string buffer;
  curl = curl_easy_init();
  if (!curl)
    printf("Curl initialization failed!\n");

  curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.1.140:3333/ping");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToString);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

  CURLcode res = curl_easy_perform(curl);

  if (res != CURLE_OK)
    printf("Update download CURL perform failed: %s\n", curl_easy_strerror(res));

  curl_easy_cleanup(curl);

  return buffer;
}

void FileDownloader::initDownload(DownloadInfo *dlInfo) {

}

void FileDownloader::startDownload() {
  curl = curl_easy_init();
  if (!curl)
    printf("Curl initialization failed!\n");
  mkdir("/SwitchDL", 0777);

  std::stringstream ss;

  ss << "/SwitchDL/file.nsp." << this->index;

  index++;

  fp = fopen(ss.str().c_str(), "wb");

  curl_easy_setopt(curl, CURLOPT_URL, "http://192.168.1.140:3333/static/SMPNO.nsp");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToFile);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
  curl_easy_setopt(curl, CURLOPT_NOPROGRESS, false);
  curl_easy_setopt(curl, CURLOPT_PROGRESSFUNCTION, calcProgress);

  CURLcode res = curl_easy_perform(curl);

  if (res != CURLE_OK)
    printf("Update download CURL perform failed: %s\n", curl_easy_strerror(res));

  fclose(fp);
  curl_easy_cleanup(curl);

}

std::string FileDownloader::formatBytes(uint bytes) {
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

int FileDownloader::calcProgress(void* ptr, double TotalToDownload, double NowDownloaded,
                    double TotalToUpload, double NowUploaded) {
    // ensure that the file to be downloaded is not empty
    // because that would cause a division by zero error later on
    if (TotalToDownload <= 0.0) {
        return 0;
    }

    if(downloadCanceled) return -1;

    // how wide you want the progress meter to be
    int totaldotz=40;
    double fractiondownloaded = NowDownloaded / TotalToDownload;
    // part of the progressmeter that's already "full"
    int dotz = round(fractiondownloaded * totaldotz);

    // create the "meter"
    int ii=0;
    printf("%s [",(formatBytes(NowDownloaded).c_str()));
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

size_t FileDownloader::writeToFile(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

size_t FileDownloader::writeToString(void *ptr, size_t size, size_t nmemb, std::string *str) {
    str->append((char*) ptr, size * nmemb);
    return size * nmemb;
}
