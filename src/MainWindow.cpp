#include "../include/StumperIDE.hpp"
#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>

StumperIDE::MainWindow::MainWindow(FileNavBar *fileNavBar, TextEditingZone *textEditingZone, FileSelectorZone *fileSelectorZone) : _mainWindow(ftxui::App::Fullscreen()),
                                                                                                                                   _fileNavBar(fileNavBar),
                                                                                                                                   _textEditingZone(textEditingZone),
                                                                                                                                   _fileSelectorZone(fileSelectorZone)
{
    _mainComponent = nullptr;

    this->_fileNavBar->SetMediator(this);
    this->_textEditingZone->SetMediator(this);
    this->_fileSelectorZone->SetMediator(this);
}

void StumperIDE::MainWindow::AddCloseWindowEvent(ftxui::Component &MainComponent)
{
    MainComponent |= ftxui::CatchEvent([&](ftxui::Event event) {
        if (event == ftxui::Event::Character('q') && _textEditingZone->TextZone->Focused() == false) {
            _mainWindow.ExitLoopClosure()();
            return true;
        }
        return false;
    });
}

void StumperIDE::MainWindow::Notify(SenderBase *sender, std::string event) const
{
    return;
}

void StumperIDE::MainWindow::Run()
{
    auto layout = ftxui::Container::Vertical({
        _fileNavBar->Toggle,
        ftxui::Container::Horizontal({_textEditingZone->TextZone, _fileSelectorZone->FileSelector})
    });

    _mainComponent = ftxui::Renderer(layout, [&] {
        return ftxui::vbox({
            _fileNavBar->Toggle->Render() | ftxui::border,
            ftxui::hbox(_textEditingZone->TextZone->Render() | ftxui::border,
                            _fileSelectorZone->FileSelector->Render())
                            | ftxui::yflex
        });
    });

    AddCloseWindowEvent(_mainComponent);

    _mainWindow.Loop(_mainComponent);
}
