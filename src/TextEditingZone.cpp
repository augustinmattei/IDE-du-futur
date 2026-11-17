#include "../include/TextEditingZone.hpp"

StumperIDE::TextEditingZone::TextEditingZone()
{
    _file_text = "Lorem Ipsum Dolor Sit Amet, c'est un test si t'avais pas remarqué...";

    TextZone = ftxui::Input(&_file_text, "");
}

void StumperIDE::TextEditingZone::DisplayText(std::string ToDisplay)
{
    _file_text = ToDisplay;
}
