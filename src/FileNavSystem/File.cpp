#include "../../include/File.hpp"
#include <string>


StumperIDE::File::File(std::string Name)
{
    this->Name = Name;
    _isSelected = false;
}
