#pragma once

#include "GlobalWindowInput.hpp"
#include "AppNotifyicon.hpp"
#include "MainWindow.hpp"

class App: public KeyboardLowLevelHandler{
private:
    bool isAltDown;
    AppNotifyicon appNotifyicon;
    HINSTANCE hInstance;
    MainWindow window;

    ULONG_PTR gdiplusToken;

    int StartWindowLoop();
protected:
    bool OnKeyDown(KBDLLHOOKSTRUCT *args);
    bool OnKeyUp(KBDLLHOOKSTRUCT *args);
public:
    App(HINSTANCE hInstance);
    bool OnKeyboardHookLL(KeyboardMessages message, KBDLLHOOKSTRUCT *args) noexcept override;
    int Run();
};