#include "../include/StumperIDE.hpp"

int main() {
    StumperIDE::FileNavBar *fileNavBar = new StumperIDE::FileNavBar({"Placeholder 1", "Placeholder 2", "Placeholder 3"});
    StumperIDE::TextEditingZone *textEditingZone = new StumperIDE::TextEditingZone();
    StumperIDE::FileSelectorZone *fileSelectorZone = new StumperIDE::FileSelectorZone();

    StumperIDE::MainWindow *mainWindow = new StumperIDE::MainWindow(fileNavBar, textEditingZone, fileSelectorZone);

    mainWindow->Run();

    delete fileNavBar;
    delete textEditingZone;
    delete fileSelectorZone;
    delete mainWindow;

    return 0;
}
