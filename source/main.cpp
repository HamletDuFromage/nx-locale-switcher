#include <switch.h>
#include <borealis.hpp>
#include "main_frame.hpp"

namespace i18n = brls::i18n;
using namespace i18n::literals;

int main(int argc, char* argv[])
{
    // Init the app
    if (!brls::Application::init(APP_TITLE))
    {
        brls::Logger::error("Unable to init Borealis application");
        return EXIT_FAILURE;
    }
    i18n::loadTranslations();
    
    // Setup verbose logging on PC
#ifndef __SWITCH__
    brls::Logger::setLogLevel(brls::LogLevel::DEBUG);
#endif

    romfsInit();
    nsInitialize();

    brls::Logger::setLogLevel(brls::LogLevel::DEBUG);
    brls::Logger::debug("Start");

    brls::Application::pushView(new MainFrame());

    while (brls::Application::mainLoop());

    nsExit();
    romfsExit();

    return EXIT_SUCCESS;
}
