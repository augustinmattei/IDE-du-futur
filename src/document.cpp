#include "../include/document.hpp"
#include <ftxui/component/component.hpp>
#include <vector>

StumperIDE::Document::Document(const std::vector<std::string> Entries) : _entries(Entries)
{
    _selected = 0;

    _document = ftxui::Menu(&_entries, &_selected);
}
