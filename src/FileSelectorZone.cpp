#include "../include/FileSelectorZone.hpp"
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>

StumperIDE::FileSelectorZone::FileSelectorZone()
{
    _file_selected = 0;
    _entries = {
        "Placeholder 1",
        "Placeholder 2",
        "Placeholder 3"
    };

    FileSelector = ftxui::Dropdown(&_entries, &_file_selected);

    FileSelector |= ftxui::CatchEvent([&](ftxui::Event event) {
        if (event == ftxui::Event::Character('\n')) {
            _mediator->Notify(this, FILE_SELECTED, _entries[_file_selected]);
            return true;
        }
        return false;
    });
}
