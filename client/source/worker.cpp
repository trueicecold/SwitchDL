#include "worker.hpp"

void threadFunc(void*);

Worker::Worker(std::function<void(void)> workerFunc, std::function<void(void)> finishedCallback)
: m_workerFunc(workerFunc), m_finishedCallback(finishedCallback) {
	
	Worker::g_runningWorkers++;
}

Worker::~Worker() {
	Worker::g_runningWorkers--;
}

void Worker::start() {
  threadCreate(&m_thread, &threadFunc, this, 0x2000, 0x2B, -2);
  threadStart(&m_thread);
}

void threadFunc(void* args) {
  ((Worker*)args)->m_workerFunc();
  ((Worker*)args)->m_finishedCallback();
  delete (Worker*)args;
}
