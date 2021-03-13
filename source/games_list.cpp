#include <games_list.hpp>
#include <SimpleIniParser.hpp>
#include <filesystem>
#include <fstream>
#include <set>
#include <utils.hpp>

namespace i18n = brls::i18n;
using namespace i18n::literals;

GamesList::GamesList() :
    brls::List()
{

}

void GamesList::AddEntry(std::string name, std::string tid, std::string language, std::string region, unsigned char* icon, size_t icon_size) {
    listItem = new brls::ListItem(name, "", 
        language.empty() && region.empty() ? tid : 
            (language.empty() ? fmt::format("{0}        ({1})",tid, region) : 
                (region.empty() ? fmt::format("{0}        ({1})",tid, language) : 
                    fmt::format("{0}        ({1} | {2})",tid, language, region)
    )));
    if(icon_size)
        listItem->setThumbnail(icon, icon_size);

    listItem->registerAction("menus/list/edit_locale"_i18n, brls::Key::A, [this, tid] { 
        PopupMenu(tid);
        return true;
    });
    this->addView(listItem);
    empty = false;
}

void GamesList::PopupMenu(std::string tid) {
    brls::TabFrame* appView = new brls::TabFrame();

    brls::List* languageList = new brls::List();
    for(const auto& language : languages) {
        brls::ListItem* languageItem = new brls::ListItem(language.first);
        languageItem->registerAction("menus/list/select_language"_i18n, brls::Key::A, [this, language, tid] {
            SetOption(tid, "override_config", "override_language", language.second);
            showDialog("menus/list/set_language_to"_i18n + language.first);
            return true;
        });
        languageList->addView(languageItem);
    }

    brls::List* regionList = new brls::List();
    for(const auto& region : regions) {
        brls::ListItem* regionItem = new brls::ListItem(region.first);
        regionItem->registerAction("menus/list/select_region"_i18n, brls::Key::A, [this, region, tid] {
            SetOption(tid, "override_config", "override_region", region.second);
            showDialog("menus/list/set_region_to"_i18n + region.first);
            return true;
        });
        regionList->addView(regionItem);
    }

    brls::List* toolsList = new brls::List();
    brls::ListItem* toolItem = new brls::ListItem("menus/list/reset_settings"_i18n);
    toolItem->registerAction("brls/hints/ok"_i18n, brls::Key::A, [this, tid] {
        resetSettings(ams_contents + tid + "/config.ini");
        showDialog("menus/list/settings_cleared"_i18n);
        return true;
    });
    toolsList->addView(toolItem);

    appView->addTab("menus/list/language"_i18n, languageList);
    appView->addTab("menus/list/region"_i18n, regionList);
    appView->addTab("menus/list/tools"_i18n, toolsList);
    brls::PopupFrame::open("menus/list/edit_locale"_i18n, appView, "", "");
}

void GamesList::SetOption(std::string tid, std::string section, std::string key, std::string value) {
    std::string path(ams_contents + tid + "/config.ini");
    createTree(path);
    simpleIniParser::Ini *ini = simpleIniParser::Ini::parseOrCreateFile(path);
    auto sec = ini->findOrCreateSection(section);
    for (auto const &option : sec->options) {
        if (option->key == key) {
            option->value = value;
            ini->writeToFile(path);
            delete ini;
            return;
        }
    }
    sec->options.push_back(new simpleIniParser::IniOption(simpleIniParser::IniOptionType::Option, key, value));
    ini->writeToFile(path);
    delete ini;
}