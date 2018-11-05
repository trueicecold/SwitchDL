#pragma once

#include <switch.h>
#include <functional>

class Worker {
public:
  ~Worker();
  static Worker* createWorker(std::function<void(void)> workerFunc, std::function<void(void)> finishedCallback) {
    return new Worker(workerFunc, finishedCallback);
  }

  Worker(const Worker&) = delete;
  Worker &operator=(const Worker&) = delete;
  Worker(Worker &&) = delete;
  Worker& operator=(Worker &&) = delete;

  void start();
  
  static inline u8 g_runningWorkers = 0;
private:
  Worker(std::function<void(void)> workerFunc, std::function<void(void)> finishedCallback);

  Thread m_thread;
  std::function<void(void)> m_workerFunc;
  std::function<void(void)> m_finishedCallback;

  friend void threadFunc(void* args);
};
