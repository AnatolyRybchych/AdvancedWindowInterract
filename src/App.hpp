#pragma once

#include "GlobalWindowInput.hpp"
#include "AppNotifyicon.hpp"

class App: public MouseLowLevelHandler, public KeyboardLowLevelHandler{
private:
    bool isAltDown;
    AppNotifyicon appNotifyicon;
    HINSTANCE hInstance;

    int StartWindowLoop();
protected:
    bool OnKeyDown(KBDLLHOOKSTRUCT *args);
    bool OnKeyUp(KBDLLHOOKSTRUCT *args);
public:
    App(HINSTANCE hInstance);
    bool OnMouseHookLL(MouseMessages message, MSLLHOOKSTRUCT *args) noexcept override;
    bool OnKeyboardHookLL(KeyboardMessages message, KBDLLHOOKSTRUCT *args) noexcept override;
    int Run();
};