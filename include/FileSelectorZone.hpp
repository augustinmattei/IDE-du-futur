#pragma once

#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <string>
#include <vector>
#include "SenderBase.hpp"

namespace StumperIDE
{
    class FileSelectorZone : public SenderBase {
        private:
            int _file_selected;
            std::vector<std::string> _entries;

        public:
            ftxui::Component FileSelector;
            FileSelectorZone();
    };
}
