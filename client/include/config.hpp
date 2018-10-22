#pragma once

#include <stdio.h>
#include <string>

extern "C" {
  #include "types.h"
}

class Config
{
  public:
    static void load();
    static void save(std::string ip_address, std::string port);
    static inline std::string IP_ADDRESS;
    static inline std::string PORT;

    Config();
    ~Config();
};
