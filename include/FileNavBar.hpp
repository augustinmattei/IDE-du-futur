#pragma once

#include <vector>
#include <string>
#include <ftxui/component/app.hpp>

namespace StumperIDE
{
    class FileNavBar {
        private:
            int _file_selected;
            std::vector<std::string> _entries;

        public:
            ftxui::Component Toggle;

            FileNavBar(const std::vector<std::string> Entries);
    };
}
