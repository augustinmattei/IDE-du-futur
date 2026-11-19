#include "../include/FileNavBar.hpp"
#include <fstream>
#include <ftxui/component/component.hpp>

StumperIDE::FileNavBar::FileNavBar(const std::vector<std::string> Entries) : _entries(Entries),
                                                                             _file_contents({"Lorem Ipsum Dolor Sit Amet, c'est un test si t'avais pas remarqué...",
                                                                                                "Ceci est un test 2",
                                                                                                "Ceci est un test 3"})
{
    _file_selected = 0;

    Toggle = ftxui::Toggle(&_entries, &_file_selected);

    Toggle |= ftxui::CatchEvent([&](ftxui::Event event) {
        if (event == ftxui::Event::Character('\n')) {
            _mediator->Notify(this, FILE_CHANGED, _file_contents[_file_selected]);
            return true;
        }
        return false;
    });
}

void StumperIDE::FileNavBar::OpenSelectedFile(const std::string Filename)
{
    std::ifstream filestream(Filename);
    std::string str;
    std::string file_content;

    while (std::getline(filestream, str)) {
        file_content += str;
        file_content.push_back('\n');
    }

    _entries.push_back(Filename);
    _file_contents.push_back("Ceci est un test d'ouverture, j'apparais sûrement plusieurs fois");
    _file_selected = _entries.size() - 1;
    filestream.close();
    _mediator->Notify(this, FILE_OPENED, _file_contents[_file_selected]);
}
