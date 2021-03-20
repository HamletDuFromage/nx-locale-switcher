#include <tools_list.hpp>
#include <utils.hpp>
#include <main_frame.hpp>

namespace i18n = brls::i18n;
using namespace i18n::literals;

ToolsList::ToolsList() :
    brls::List()
{
    resetAll = new brls::ListItem("menus/tools/reset_all"_i18n);
    resetAll->registerAction("brls/hints/ok"_i18n, brls::Key::A, [this] {
        util::resetAllSettings();
        util::showDialog("menus/common/all_done"_i18n);
        return true;
    });
    this->addView(resetAll);

    reload = new brls::ListItem("menus/tools/reload"_i18n);
    reload->registerAction("brls/hints/ok"_i18n, brls::Key::A, [this] {
        brls::Application::pushView(new MainFrame());
        return true;
    });
    this->addView(reload);
}