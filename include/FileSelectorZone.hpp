#pragma once

#include <filesystem>
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
            int _fileSelected;
            float _scrollY = 0.0f;
            std::vector<std::string> _entries;
            std::vector<ftxui::Component> _fileEntries;

            std::vector<ftxui::Component> BuildEntries(std::filesystem::path ParentPath);

        public:
            ftxui::Component FileSelector;
            FileSelectorZone();
    };
}
