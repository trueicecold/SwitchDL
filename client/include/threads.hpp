#pragma once

#include <switch.h>

namespace Threads {

  Result create(ThreadFunc func, void* args);
  void joinAll();

}
