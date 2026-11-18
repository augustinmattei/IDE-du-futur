#pragma once

#include "SenderEvent.hpp"
#include <string>

namespace StumperIDE
{
    class SenderBase;

    class IMediator {
        public:
            virtual void Notify(SenderBase *sender, sender_event_t type, std::string file_content) const = 0;
    };
}
