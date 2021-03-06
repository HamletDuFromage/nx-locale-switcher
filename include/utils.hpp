#pragma once

#include <string>

namespace util {

    constexpr char ams_contents[] = "/atmosphere/contents/";

    void createTree(std::string path);
    void resetSettings(std::string path);
    void resetAllSettings();
    void showDialog(std::string msg);

}
