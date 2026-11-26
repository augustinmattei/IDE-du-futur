#pragma once

#include <cstddef>
#include <ftxui/component/app.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include <vector>

namespace StumperIDE
{
    class TextEditingZone : public ftxui::ComponentBase {
        private:
            size_t VisibleHeight() const;
            size_t LineNumberWidth() const;
            std::string LineNumberText(size_t line_index, size_t width) const;
            void UpdateScroll();
            static bool IsWordCharacter(char character);
            bool IsCharacterSelected(size_t x, size_t y) const;
            void BeginSelection();
            void SetCursorInBufferBounds();
            void MoveCursorHome();
            void MoveCursorEnd();
            void MoveCursorLeft();
            void MoveCursorRight();
            void MoveCursorUp();
            void MoveCursorDown();
            void MoveCursorToPreviousWord();
            void MoveCursorToNextWord();

            std::vector<std::string> fileText;
            std::string currentFilepath = "untitled.txt";
            size_t cursorX = 0;
            size_t cursorY = 0;
            size_t scrollY = 0;
            size_t selectionAnchorX = 0;
            size_t selectionAnchorY = 0;
            bool hasSelection = false;

            ftxui::Box editorBox;

        public:
            TextEditingZone();

            ftxui::Element OnRender() override;
            bool OnEvent(ftxui::Event event) override;
            bool Focusable() const override;

            void SaveToFile(const std::string &path);
            void LoadFromFile(const std::string &path);
            const std::string &CurrentFilePath() const;

            bool HasSelection() const;
            std::string GetSelectedText() const;
            void DeleteSelection();
            void ClearSelection();

            std::string GetCurrentLineText() const;
            void DeleteCurrentLine();
    };
}
