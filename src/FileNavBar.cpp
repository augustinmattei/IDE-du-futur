#include "../include/FileNavBar.hpp"
#include <fstream>

StumperIDE::FileNavBar::FileNavBar(const std::vector<std::string> Entries) : _entries(Entries)
{
    _file_selected = 0;

    Toggle = ftxui::Toggle(&_entries, &_file_selected);
}

std::string StumperIDE::FileNavBar::OpenSelectedFile(const std::string Filename)
{
    std::ifstream filestream(Filename);
    std::string str;
    std::string file_content;

    while (std::getline(filestream, str)) {
        file_content += str;
        file_content.push_back('\n');
    }

    return file_content;
}
