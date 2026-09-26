#include <string>

namespace StumperIDE
{
    class IFileObject {
        public:
            std::string getName() { return Name; }

        protected:
            std::string Name;
    };
}
