#pragma once

#include <string>

namespace StumperIDE
{
    class SenderBase;

    class IMediator {
        public:
            virtual void Notify(SenderBase *sender, std::string event) = 0;
    };
}
