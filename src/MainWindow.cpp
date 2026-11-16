#include "../include/StumperIDE.hpp"
#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>

StumperIDE::MainWindow::MainWindow() : _mainWindow(ftxui::App::Fullscreen()), _mainElement({
        "Test 1",
        "Test 2",
        "Test 3"
    })
{

}

void StumperIDE::MainWindow::Run()
{
    auto layout = ftxui::Container::Horizontal({
        _mainElement._document
    });

    auto mainComponent = ftxui::Renderer(layout, [&] {
        return ftxui::hbox({
            _mainElement._document->Render()
        }) | ftxui::xflex | ftxui::size(ftxui::WIDTH, ftxui::GREATER_THAN, 40) | ftxui::border;
    });

    _mainWindow.Loop(mainComponent);
}
