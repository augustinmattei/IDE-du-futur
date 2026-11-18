#include "../include/SenderBase.hpp"

StumperIDE::SenderBase::SenderBase(StumperIDE::IMediator *mediator) : _mediator(mediator) {}

void StumperIDE::SenderBase::SetMediator(StumperIDE::IMediator *mediator) {
    this->_mediator = mediator;
}
