#include <string>
#include "IFileObject.hpp"

namespace StumperIDE {
    class File : public IFileObject {
        private:
            bool _isSelected;

        public:
            File(std::string Name);
    };
}
