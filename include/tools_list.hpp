#pragma once

#include <borealis.hpp>

class ToolsList : public brls::List
{
    private:
        brls::ListItem* resetAll;
        brls::ListItem* reload;

    public:
        ToolsList();

};