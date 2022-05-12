#pragma once
#include "UnicodeWindows.hpp"
#include "MouseMessages.hpp"

class MouseLowLevelHandler
{
public:
    virtual void OnMouseHookLL(MouseMessages message, MSLLHOOKSTRUCT *args) noexcept = 0;
};