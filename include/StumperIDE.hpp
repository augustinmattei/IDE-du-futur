#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>

namespace StumperIDE {
    class MainWindow {
        private:
            ftxui::Element document;
            ftxui::Screen _mainWindow;

        public:
            MainWindow();
            void Run();
    };
}
