#pragma once

#include "IMediator.hpp"

namespace StumperIDE
{
    class SenderBase {
        protected:
            IMediator *_mediator;

        public:
            SenderBase(IMediator *mediator = nullptr);

            void SetMediator(IMediator *mediator);
    };
}
