#pragma once

#include <borealis.hpp>
#include "games_list.hpp"

class MainFrame : public brls::TabFrame
{
    private:
        GamesList* allGames;
        GamesList* editedGames;

    public:
        MainFrame();
        void PopulateLists();
        void PopulatePage();
};
