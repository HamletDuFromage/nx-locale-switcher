#include "main_frame.hpp"
#include "about_tab.hpp"
#include "tools_list.hpp"
#include <switch.h>
#include <filesystem>
#include <SimpleIniParser.hpp>
#include <utils.hpp>

namespace i18n = brls::i18n;
using namespace i18n::literals;

MainFrame::MainFrame() : TabFrame()
{
    this->setIcon("romfs:/gui_icon.png");
    this->setTitle(std::string(APP_TITLE));

    this->setFooterText("v" + std::string(APP_VERSION));

    this->allGames = new GamesList();
    this->editedGames = new GamesList();
    this->PopulateLists();

    this->addTab("menus/main/about"_i18n, new AboutTab());
    if(!this->allGames->isEmpty())
        this->addTab("menus/main/all_games_label"_i18n, this->allGames);
    if(!this->editedGames->isEmpty())
        this->addTab("menus/main/edited_games_label"_i18n, this->editedGames);
    
    this->addTab("menus/main/tools"_i18n, new ToolsList());

    this->registerAction("" , brls::Key::B, [this] { return true; });
    this->registerAction("menus/tools/reload"_i18n , brls::Key::Y, [this] {
        brls::Application::pushView(new MainFrame());
        return true; 
    });
}

void MainFrame::PopulateLists() {
    NsApplicationRecord record = {0};
    uint64_t tid = 0;
    NsApplicationControlData controlData = {0};
    NacpLanguageEntry* langEntry = NULL;

    Result rc           = 0;
    size_t i            = 0;
    int recordCount     = 0;
    size_t controlSize  = 0;

    while (true)
    {
        rc = nsListApplicationRecord(&record, sizeof(record), i, &recordCount);
        if (R_FAILED(rc)) break;
        if(recordCount <= 0) break;

        tid = record.application_id;
        rc = nsGetApplicationControlData(NsApplicationControlSource_Storage, tid, &controlData, sizeof(controlData), &controlSize);
        if (R_FAILED(rc)) break;
        rc = nacpGetLanguageEntry(&controlData.nacp, &langEntry);
        if (R_FAILED(rc)) break;
        
        if (!langEntry->name) {
            i++;
            continue;
        }
        std::string tidstr = fmt::format("{:016X}", tid);
        this->allGames->AddEntry(std::string(langEntry->name), tidstr, "", "", controlData.icon, sizeof(controlData.icon));
        std::string iniFile = util::ams_contents + tidstr + "/config.ini";
        if(std::filesystem::exists(iniFile)) {
            std::string region;
            std::string language;
            bool edited = false;
            simpleIniParser::Ini *ini = simpleIniParser::Ini::parseFile(iniFile);
            for (auto const &section : ini->sections) {
                if (section->type != simpleIniParser::IniSectionType::Section)
                    continue;

                if (section->value == "override_config") {
                    for (auto const &option : section->options) {
                        if (option->key == "override_language") {
                            language = option->value;
                            edited = true;
                        }
                        if (option->key == "override_region") {
                            region = option->value;
                            edited = true;
                        }
                    }
                    break;
                }
            }
            delete ini;
            if(edited) {
                this->editedGames->AddEntry(
                    std::string(langEntry->name),tidstr,
                    language, region,
                    controlData.icon, sizeof(controlData.icon)
                );
            }
        }
        i++;
    }
}
