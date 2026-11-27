#include "../include/App.hpp"
#include "../include/TextEditingZone.hpp"
#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/dom/node.hpp>
#include <ftxui/screen/screen.hpp>
#include <memory>

StumperIDE::StumperIDEApp::StumperIDEApp()
    :   _textEditor(ftxui::Make<TextEditingZone>()),
        _screen(ftxui::App::Fullscreen())
{
    _bodyContainer = ftxui::Container::Horizontal({
        _textEditor,
    });

    _mainContainer = ftxui::Container::Vertical({
        _bodyContainer,
    });

    _rootContainer = ftxui::Container::Tab({
        _mainContainer
    }, &_focusedLayer);

    _renderer = ftxui::Renderer(_rootContainer, [this] { return Render(); });

    _globalShortcuts = ftxui::CatchEvent(_renderer, [this](ftxui::Event event) { return HandleGlobalEvent(event); });

    FocusTextEditingZone();
}

ftxui::Element StumperIDE::StumperIDEApp::Render()
{
    const auto editor = std::static_pointer_cast<TextEditingZone>(_textEditor);

    ftxui::Element workspace = _textEditor->Render() | ftxui::xflex;

    ftxui::Element layout = ftxui::vbox({
        ftxui::text("StumperIDE v0.0.1 - IDE le plus performant de ton quartier") | ftxui::bold,
        ftxui::separator(),
        workspace | ftxui::yflex,
        ftxui::separator(),
        ftxui::text(" File: " + editor->CurrentFilePath())
    });

    return layout;

    // ftxui::Elements layers = {layout};

    // return ftxui::dbox(std::move(layers));
}

void StumperIDE::StumperIDEApp::Run()
{
    _screen.ForceHandleCtrlC(false);
    _screen.Loop(_globalShortcuts);
}

void StumperIDE::StumperIDEApp::FocusTextEditingZone()
{
    _focusedLayer = 0;
    _textEditor->TakeFocus();
}

bool StumperIDE::StumperIDEApp::HandleGlobalEvent(ftxui::Event event)
{
    return false;
}
