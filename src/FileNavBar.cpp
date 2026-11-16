#include "../include/FileNavBar.hpp"
#include <ftxui/component/component.hpp>
#include <vector>

StumperIDE::FileNavBar::FileNavBar(const std::vector<std::string> Entries) : _entries(Entries)
{
    _file_selected = 0;

    Toggle = ftxui::Toggle(&_entries, &_file_selected);
}
