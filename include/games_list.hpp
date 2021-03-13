#pragma once

#include <borealis.hpp>

namespace i18n = brls::i18n;
using namespace i18n::literals;

class GamesList : public brls::List
{
    private:
        brls::ListItem* listItem;
        bool empty = true;
        std::vector<std::pair<std::string, std::string>> languages{
            std::make_pair("menus/language/en-US"_i18n, "en-US"),
            std::make_pair("menus/language/ja"_i18n, "ja"),
            std::make_pair("menus/language/fr"_i18n, "fr"),
            std::make_pair("menus/language/de"_i18n, "de"),
            std::make_pair("menus/language/it"_i18n, "it"),
            std::make_pair("menus/language/es"_i18n, "es"),
            std::make_pair("menus/language/zh-CN"_i18n, "zh-CN"),
            std::make_pair("menus/language/ko"_i18n, "ko"),
            std::make_pair("menus/language/nl"_i18n, "nl"),
            std::make_pair("menus/language/pt"_i18n, "pt"),
            std::make_pair("menus/language/ru"_i18n, "ru"),
            std::make_pair("menus/language/zh-TW"_i18n, "zh-TW"),
            std::make_pair("menus/language/en-GB"_i18n, "en-GB"),
            std::make_pair("menus/language/fr-CA"_i18n, "fr-CA"),
            std::make_pair("menus/language/es-419"_i18n, "es-419"),
            std::make_pair("menus/language/zh-Hant"_i18n, "zh-Hant"),
            std::make_pair("menus/language/zh-Hans"_i18n, "zh-Hans")
        };

        std::vector<std::pair<std::string, std::string>> regions{
            std::make_pair("menus/region/jpn"_i18n, "jpn"),
            std::make_pair("menus/region/usa"_i18n, "usa"),
            std::make_pair("menus/region/eur"_i18n, "eur"),
            std::make_pair("menus/region/aus"_i18n, "aus"),
            std::make_pair("menus/region/chn"_i18n, "chn"),
            std::make_pair("menus/region/kor"_i18n, "kor"),
            std::make_pair("menus/region/twn"_i18n, "twn")
        };

    public:
        GamesList();
        void AddEntry(std::string name, std::string tid = "", std::string language = "", std::string region = "", unsigned char* icon = NULL, size_t icon_size = 0);
        void PopupMenu(std::string tid);
        void SetOption(std::string path, std::string section, std::string key, std::string value);
        inline bool isEmpty() { return empty; }
};