#include "../include/TextEditingZone.hpp"
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/mouse.hpp>
#include <ftxui/dom/elements.hpp>
#include <stdexcept>

struct Position {
    size_t x = 0;
    size_t y = 0;
};

bool HasInferiorPosition(const Position &left, const Position &right)
{
    return left.y < right.y || (left.y == right.y && left.x < right.x);
}

Position ClampedPosition(Position position, const std::vector<std::string> &lines)
{
    if (lines.empty()) {
        return {};
    }

    position.y = std::min(position.y, lines.size() - 1);
    position.x = std::min(position.x, lines[position.y].size());
    return position;
}

std::pair<Position, Position> OrderedSelection(Position anchor, Position cursor, const std::vector<std::string> &lines)
{
    anchor = ClampedPosition(anchor, lines);
    cursor = ClampedPosition(cursor, lines);
    if (HasInferiorPosition(cursor, anchor)) {
        std::swap(anchor, cursor);
    }

    return {anchor, cursor};
}

StumperIDE::TextEditingZone::TextEditingZone()
{
    fileText.push_back("");
}

ftxui::Element StumperIDE::TextEditingZone::OnRender()
{
    UpdateScroll();

    ftxui::Elements file_lines;
    const size_t visible_height = VisibleHeight();
    const size_t last_visible_line = std::min(file_lines.size(), scrollY + visible_height);
    const size_t line_number_width = LineNumberWidth();

    for (size_t y = scrollY; y < last_visible_line; ++y) {
        const std::string &line_content = fileText[y];

        ftxui::Element line_number = ftxui::text(LineNumberText(y, line_number_width));

        ftxui::Elements line_parts{line_number};
        const size_t cursor_x = (y == cursorY ? std::min(cursorX, line_content.size()) : 0);
        for (size_t x = 0; x <= line_content.size(); ++x) {
            if (y == cursorY && x == cursor_x) {
                line_parts.push_back(ftxui::text("❚") | ftxui::blink);
            }

            if (x == line_content.size()) {
                continue;
            }

            ftxui::Element character = ftxui::text(line_content.substr(x, 1));
            if (IsCharacterSelected(x, y)) {
                character = character | ftxui::color(ftxui::Color::Red);
            } else {
                character = character | ftxui::color(ftxui::Color::Black);
            }
            line_parts.push_back(std::move(character));
        }
        file_lines.push_back(ftxui::hbox(std::move(line_parts)));
    }

    while (file_lines.size() < visible_height) {
        file_lines.push_back(ftxui::hbox({
            ftxui::text(std::string(line_number_width, ' ') + " | "),
        }));
    }

    return ftxui::vbox(std::move(file_lines)) | ftxui::reflect(editorBox);
}

void StumperIDE::TextEditingZone::SaveToFile(const std::string &path)
{
    const std::string save_path = path.empty() ? currentFilepath : path;
    std::ofstream file(save_path);
    if (!file) {
        throw std::runtime_error("Can't save file : " + save_path);
    }

    for (size_t i = 0; i < fileText.size(); ++i) {
        file << fileText[i];
        if (i + 1 < fileText.size()) {
            file << '\n';
        }
    }

    currentFilepath = save_path;
}

void StumperIDE::TextEditingZone::LoadFromFile(const std::string &path)
{
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Can't open file : " + path);
    }

    fileText.clear();
    std::string line;
    while (std::getline(file, line)) {
        fileText.push_back(line);
    }

    if (fileText.empty()) {
        fileText.push_back("");
    }

    currentFilepath = path;
    cursorX = 0;
    cursorY = 0;
    scrollY = 0;
    ClearSelection();
}

const std::string& StumperIDE::TextEditingZone::CurrentFilePath() const
{
    return currentFilepath;
}

bool StumperIDE::TextEditingZone::HasSelection() const
{
    return hasSelection && (cursorX != selectionAnchorX || cursorY != selectionAnchorY);
}

std::string StumperIDE::TextEditingZone::GetSelectedText() const
{
    if (!HasSelection()) {
        return "";
    }

    auto [start, end] = OrderedSelection(
        {selectionAnchorX, selectionAnchorY},
        {cursorX, cursorY},
        fileText);

    if (start.y == end.y) {
        return fileText[start.y].substr(start.x, end.x - start.x);
    }

    std::string selected = fileText[start.y].substr(start.x);
    selected.push_back('\n');
    for (size_t y = start.y + 1; y < end.y; ++y) {
        selected += fileText[y];
        selected.push_back('\n');
    }
    selected += fileText[end.y].substr(0, end.x);
    return selected;
}

void StumperIDE::TextEditingZone::DeleteSelection()
{
    if (!HasSelection()) {
        return;
    }

    auto [start, end] = OrderedSelection(
        {selectionAnchorX, selectionAnchorY},
        {cursorX, cursorY},
        fileText);

    if (start.y == end.y) {
        fileText[start.y].erase(start.x, end.x - start.x);
    } else {
        fileText[start.y] = fileText[start.y].substr(0, start.x) + fileText[start.y].substr(end.x);
        fileText.erase(
            fileText.begin() + static_cast<std::ptrdiff_t>(start.y + 1),
            fileText.begin() + static_cast<std::ptrdiff_t>(end.y + 1));
    }

    if (fileText.empty()) {
        fileText.push_back("");
    }

    cursorX = start.x;
    cursorY = start.y;
    ClearSelection();
    UpdateScroll();
}

void StumperIDE::TextEditingZone::ClearSelection()
{
    SetCursorInBufferBounds();
    hasSelection = false;
    selectionAnchorX = cursorX;
    selectionAnchorY = cursorY;
}

bool StumperIDE::TextEditingZone::Focusable() const {
    return true;
}

size_t StumperIDE::TextEditingZone::VisibleHeight() const
{
    if (editorBox.y_max >= editorBox.y_min) {
        return static_cast<size_t>(std::max(1, editorBox.y_max - editorBox.y_min + 1));
    }
    return 1;
}

size_t StumperIDE::TextEditingZone::LineNumberWidth() const
{
    return std::to_string(fileText.size()).size();
}

std::string StumperIDE::TextEditingZone::LineNumberText(size_t line_index, size_t width) const
{
    std::string line_number = std::to_string(line_index + 1);
    if (line_number.size() < width) {
        line_number.insert(line_number.begin(), width - line_number.size(), ' ');
    }

    return line_number + " | ";
}

void StumperIDE::TextEditingZone::UpdateScroll()
{
    const size_t visible_height = VisibleHeight();
    if (cursorY < scrollY) {
        scrollY = cursorY;
    } else if (cursorY >= scrollY + visible_height) {
        scrollY = cursorY - visible_height + 1;
    }

    if (fileText.size() <= visible_height) {
        scrollY = 0;
        return;
    }

    const size_t max_scroll = fileText.size() - visible_height;
    scrollY = std::min(scrollY, max_scroll);
}

bool StumperIDE::TextEditingZone::IsWordCharacter(char character)
{
    return std::isalnum(static_cast<unsigned char>(character) || character == '_');
}

bool StumperIDE::TextEditingZone::IsCharacterSelected(size_t x, size_t y) const
{
    if (!HasSelection()) {
        return false;
    }

    auto [start, end] = OrderedSelection(
        {selectionAnchorX, selectionAnchorY},
        {cursorX, cursorY},
        fileText);
    const Position character_pos{x, y};
    return !HasInferiorPosition(character_pos, start) && HasInferiorPosition(character_pos, end);
}

void StumperIDE::TextEditingZone::BeginSelection()
{
    if (!hasSelection) {
        selectionAnchorX = cursorX;
        selectionAnchorY = cursorY;
    }
    hasSelection = true;
}

void StumperIDE::TextEditingZone::SetCursorInBufferBounds()
{
    if (fileText.empty()) {
        fileText.push_back("");
    }

    cursorY = std::min(cursorY, fileText.size() - 1);
    cursorX = std::min(cursorX, fileText[cursorY].size());
}

bool StumperIDE::TextEditingZone::OnEvent(ftxui::Event event)
{
    if (event.is_mouse()) {
        auto mouse = event.mouse();

        bool inside_editor = (mouse.x >= editorBox.x_min && mouse.x <= editorBox.x_max &&
                              mouse.y >= editorBox.y_min && mouse.y <= editorBox.y_min);

        if (inside_editor) {
            if (mouse.button == ftxui::Mouse::Left && mouse.motion == ftxui::Mouse::Pressed) {
                TakeFocus();
                ClearSelection();
                return true;
            }

            if (mouse.motion != ftxui::Mouse::Pressed && mouse.motion != ftxui::Mouse::Released) {
                return true;
            }
        }
    }

    if (event.is_character()) {
        if (HasSelection()) {
            DeleteSelection();
        }
        fileText[cursorY].insert(cursorX, event.input());
        cursorX += event.input().size();
        ClearSelection();
        UpdateScroll();
        return true;
    }

    return ftxui::ComponentBase::OnEvent(event);
}
