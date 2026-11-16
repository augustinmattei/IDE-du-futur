#include "../include/FileSelectorZone.hpp"
#include <ftxui/component/component.hpp>

StumperIDE::FileSelectorZone::FileSelectorZone()
{
    _file_selected = 0;
    _entries = {
        "Placeholder 1",
        "Placeholder 2",
        "Placeholder 3"
    };

    FileSelector = ftxui::Dropdown(&_entries, &_file_selected);
}
