#include "../include/TextEditingZone.hpp"
#include <ftxui/component/component.hpp>

StumperIDE::TextEditingZone::TextEditingZone()
{
    _file_text = "Sélectionnez un fichier pour en afficher le contenu.";

    TextZone = ftxui::Input(&_file_text, "");

    TextZone |= ftxui::CatchEvent([&](ftxui::Event event) {
        if (event == ftxui::Event::Escape) {
            return true; //TO-DO : make TextZone lose focus upon pressing esc
        }
        return false;
    });
}

void StumperIDE::TextEditingZone::DisplayText(std::string ToDisplay)
{
    _file_text = ToDisplay;
}
