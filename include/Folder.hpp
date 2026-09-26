#include "IFileObject.hpp"

namespace StumperIDE
{
    class Folder : public IFileObject {
        private:
            bool _isOpen;

        public:
            Folder(std::string Name);
    };
}
