#include "config.hpp"

#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

Config::Config()
{
    Config::IP_ADDRESS = "";
    Config::PORT = "";
    Config::load();
    printf("CONFIG LOAD\n");
}

Config::~Config()
{
}

void Config::save(std::string ip_address, std::string port) {
    FILE* fp;

    mkdir("/SwitchDL", 0777);
    fp = fopen("/SwitchDL/config.json", "w");
    fputs(("{\"address\":\"" + ip_address + "\", \"port\":\"" + port + "\"}").c_str(), fp);
    fclose(fp);

    Config::IP_ADDRESS = ip_address;
    Config::PORT = port;
}

void Config::load() {
    json configJson;

    try {
        std::ifstream config_file("/SwitchDL/config.json");
        configJson = json::parse(config_file);
        Config::IP_ADDRESS = configJson["address"];
        Config::PORT = configJson["port"];
    } catch (json::parse_error& e) {
        Config::IP_ADDRESS = "";
        Config::PORT = "";
	}
}