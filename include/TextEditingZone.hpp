#pragma once

#include "SenderBase.hpp"
#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

namespace StumperIDE
{
    class TextEditingZone : public SenderBase {
        private:
            std::string _file_text;

        public:
            ftxui::Component TextZone;

            TextEditingZone();

            void DisplayText(std::string ToDisplay);
    };
}
