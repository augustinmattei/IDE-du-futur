#include "../include/FileSelectorZone.hpp"
#include <filesystem>
#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/event.hpp>
#include <ftxui/dom/elements.hpp>
#include <memory>
#include <vector>


ftxui::Component Empty()
{
    return std::make_shared<ftxui::ComponentBase>();
}

ftxui::Component Inner(std::vector<ftxui::Component> Children)
{
    ftxui::Component vlist = ftxui::Container::Vertical(std::move(Children));
    return ftxui::Renderer(vlist, [vlist] {
        return ftxui::hbox({
            ftxui::text(" "),
            vlist->Render(),
        });
    });
}

std::string GetFileBaseName(std::string const &path)
{
    return path.substr(path.find_last_of("/\\") + 1);
}

std::vector<ftxui::Component> StumperIDE::FileSelectorZone::BuildEntries(std::filesystem::path ParentPath = "")
{
    for (std::filesystem::directory_iterator it(ParentPath), end; it != end; ++it) {
        if (it->is_directory() && GetFileBaseName(it->path().string()).starts_with('.') == false) {
            _fileEntries.emplace(_fileEntries.begin(),
                            ftxui::Collapsible(GetFileBaseName(it->path().string()), Inner(BuildEntries(it->path()))));
        }
        if (it->is_regular_file()) {
            _fileEntries.push_back(ftxui::Button(GetFileBaseName(it->path().string()), nullptr) |
            ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 4) |
            ftxui::xflex);
        }
    }
    return _fileEntries;
}

StumperIDE::FileSelectorZone::FileSelectorZone()
{
    auto current_path = std::filesystem::current_path();

    FileSelector = ftxui::Collapsible(GetFileBaseName(current_path.string()), Inner(BuildEntries("./")));

    FileSelector = FileSelector |
                   ftxui::focusPositionRelative(0.f, _scrollY) |
                   ftxui::hscroll_indicator | ftxui::xframe |
                   ftxui::vscroll_indicator | ftxui::yframe | ftxui::border;

    FileSelector |= ftxui::CatchEvent([&](ftxui::Event event) {
        if (event.is_mouse()) {
            if (event.mouse().button == ftxui::Mouse::WheelDown) {
                _scrollY = std::min(1.0f, _scrollY + 0.05f);
                return true;
            }
            if (event.mouse().button == ftxui::Mouse::WheelUp) {
                _scrollY = std::max(0.0f, _scrollY - 0.05f);
                return true;
            }
        }
        if (event == ftxui::Event::ArrowDown) {
            _scrollY = std::min(1.0f, _scrollY + 0.05f);
            return true;
        }
        if (event == ftxui::Event::ArrowUp) {
            _scrollY = std::max(0.0f, _scrollY - 0.05f);
            return true;
        }
        return false;
    });
}
