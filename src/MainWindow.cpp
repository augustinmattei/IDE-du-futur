#include "../include/StumperIDE.hpp"
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>

StumperIDE::MainWindow::MainWindow() : _mainWindow(ftxui::Screen::Create(
                                            ftxui::Dimension::Full(),
                                            ftxui::Dimension::Full()
                                            ))
{
    MainWindow::document = ftxui::hbox({
        ftxui::text("left") | ftxui::border,
        ftxui::text("middle") | ftxui::border | ftxui::flex,
        ftxui::text("right") | ftxui::border,
    });
}

void StumperIDE::MainWindow::Run()
{
    ftxui::Render(_mainWindow, document);

    _mainWindow.Print();
}
