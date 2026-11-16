#include <vector>
#include <string>
#include <ftxui/component/app.hpp>

namespace StumperIDE {
    class Document {
        private:
            int _selected;
            const std::vector<std::string> _entries;

        public:
            ftxui::Component _document;

            Document(const std::vector<std::string> Entries);
    };
}
