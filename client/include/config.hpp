#pragma once

#include <stdio.h>
#include <string>

extern "C" {
  #include "types.h"
}

class Config
{
  public:
    void load();
    void save();
    std::string IP_ADDRESS;
    std::string PORT;

    Config();
    ~Config();
};
