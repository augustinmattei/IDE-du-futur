#include "../include/StumperIDE.hpp"
#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>

StumperIDE::MainWindow::MainWindow() : _mainWindow(ftxui::App::Fullscreen()), _fileNavBar({
        "Placeholder 1",
        "Placeholder 2",
        "Placeholder 3"
    })
{

}

void StumperIDE::MainWindow::AddCloseWindowEvent(ftxui::Component &MainComponent)
{
    MainComponent |= ftxui::CatchEvent([&](ftxui::Event event) {
        if (event == ftxui::Event::Character('q') && _textEditingZone.TextZone->Focused() == false) {
            _mainWindow.ExitLoopClosure()();
            return true;
        }
        return false;
    });
}

void StumperIDE::MainWindow::Run()
{
    auto layout = ftxui::Container::Vertical({
        _fileNavBar.Toggle,
        ftxui::Container::Horizontal({_textEditingZone.TextZone, _fileSelectorZone.FileSelector})
    });

    _mainComponent = ftxui::Renderer(layout, [&] {
        return ftxui::vbox({
            _fileNavBar.Toggle->Render() | ftxui::border,
            ftxui::hbox(_textEditingZone.TextZone->Render() | ftxui::border,
                            _fileSelectorZone.FileSelector->Render())
                            | ftxui::yflex
        });
    });

    AddCloseWindowEvent(_mainComponent);

    _mainWindow.Loop(_mainComponent);
}
