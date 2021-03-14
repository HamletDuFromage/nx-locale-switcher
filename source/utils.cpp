#include <utils.hpp>
#include <filesystem>
#include <SimpleIniParser.hpp>
#include <set>
#include <borealis.hpp>

namespace i18n = brls::i18n;
using namespace i18n::literals;

void createTree(std::string path) {
    std::string delimiter = "/";
    size_t pos = 0;
    std::string token;
    std::string directories("");
    while ((pos = path.find(delimiter)) != std::string::npos) {
        token = path.substr(0, pos);
        directories += token + "/";
        std::filesystem::create_directory(directories);
        path.erase(0, pos + delimiter.length());
    }
}

void resetSettings(std::string path) {
    std::set<std::string> options{
        "override_language",
        "override_region"
    };
    if(std::filesystem::exists(path)) {
        simpleIniParser::Ini *ini = simpleIniParser::Ini::parseFile(path);
        auto sec = ini->findSection("override_config");
        if(sec != nullptr) {
            for (const auto& option : options) {
                sec->deleteOptions(option);
            }
        }

        if(sec->options.empty()) {
            ini->deleteSection("override_config");
        }
        ini->writeToFile(path);
        delete ini;
        std::filesystem::path filePath(path);
        if(!std::filesystem::file_size(filePath)) {
            std::filesystem::remove(filePath);
            remove(filePath.parent_path().string().c_str());
        }
    }
}

void resetAllSettings() {
    for (const auto & entry : std::filesystem::recursive_directory_iterator(ams_contents)) {
        if(entry.path().filename() == "config.ini") {
            resetSettings(entry.path().string());
        }
    }
}

void showDialog(std::string msg) {
    brls::Dialog* dialog = new brls::Dialog(msg);
    brls::GenericEvent::Callback callback = [dialog](brls::View* view) {
        dialog->close();
    };
    dialog->addButton("brls/hints/ok"_i18n, callback);
    dialog->setCancelable(true);
    dialog->open();
}