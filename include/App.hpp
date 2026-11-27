#pragma once

#include <ftxui/component/app.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

namespace StumperIDE
{
    class StumperIDEApp {
        private:
            void FocusTextEditingZone();
            ftxui::Element Render();
            bool HandleGlobalEvent(ftxui::Event event);

            ftxui::Component _textEditor;
            ftxui::App _screen;

            ftxui::Component _bodyContainer;
            ftxui::Component _mainContainer;
            ftxui::Component _rootContainer;
            ftxui::Component _renderer;
            ftxui::Component _globalShortcuts;

            int _focusedLayer = 0;
        public:
            StumperIDEApp();
            void Run();
    };
}
