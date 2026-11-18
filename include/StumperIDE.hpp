#pragma once

#include <ftxui/component/app.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "FileNavBar.hpp"
#include "IMediator.hpp"
#include "SenderEvent.hpp"
#include "TextEditingZone.hpp"
#include "FileSelectorZone.hpp"

namespace StumperIDE
{
    class MainWindow : public IMediator {
        private:
            FileNavBar *_fileNavBar;
            TextEditingZone *_textEditingZone;
            FileSelectorZone *_fileSelectorZone;

            ftxui::App _mainWindow;
            ftxui::Component _mainComponent;
        public:
            MainWindow(FileNavBar *fileNavBar, TextEditingZone *textEditingZone, FileSelectorZone *fileSelectorZone);
            void Run();

            void Notify(SenderBase *sender, sender_event_t type, std::string file_content) const;

            void AddCloseWindowEvent(ftxui::Component &MainComponent);
        };
}
