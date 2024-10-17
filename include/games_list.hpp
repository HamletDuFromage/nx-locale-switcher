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
            std::make_pair("American English (en-US)", "en-US"),
            std::make_pair("日本語 (ja)", "ja"),
            std::make_pair("Français (fr)", "fr"),
            std::make_pair("Deutsch (de)", "de"),
            std::make_pair("Italiano (it)", "it"),
            std::make_pair("Español (es)", "es"),
            std::make_pair("简体中文 (zh-CN)", "zh-CN"),
            std::make_pair("한국어 (ko)", "ko"),
            std::make_pair("Nederlands (nl)", "nl"),
            std::make_pair("Português (pt)", "pt"),
            std::make_pair("Русский (ru)", "ru"),
            std::make_pair("繁體中文 (zh-TW)", "zh-TW"),
            std::make_pair("English (Great Britain) (en-GB)", "en-GB"),
            std::make_pair("Français (Canada) (fr-CA)", "fr-CA"),
            std::make_pair("Español (Latinoamérica) (es-419)", "es-419"),
            std::make_pair("Traditional Chinese (zh-Hant)", "zh-Hant"),
            std::make_pair("Simplified Chinese (zh-Hans)", "zh-Hans"),
            std::make_pair("Português (Brasil) (pt-BR)", "pt-BR")
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
