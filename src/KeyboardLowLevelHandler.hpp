#pragma once
#include "UnicodeWindows.hpp"
#include "KeyboardMessages.hpp"

class KeyboardLowLevelHandler
{
public:
    virtual void OnKeyboardHookLL(KeyboardMessages message, KBDLLHOOKSTRUCT *args) noexcept = 0;
};