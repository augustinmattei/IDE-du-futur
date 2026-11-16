#include <ftxui/component/app.hpp>
#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>
#include "document.hpp"

namespace StumperIDE {
    class MainWindow {
        private:
            Document _mainElement;
            ftxui::App _mainWindow;

        public:
            MainWindow();
            void Run();
    };
}
