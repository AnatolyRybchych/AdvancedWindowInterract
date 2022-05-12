#pragma once
#include <stdexcept>

#include "UnicodeWindows.hpp"
#include "MouseMessages.hpp"
#include "MouseLowLevelHandler.hpp"
#include "KeyboardLowLevelHandler.hpp"

LRESULT CALLBACK LowLevelMouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK LowLevelkeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);

class GlobalWindowInput{
    friend LRESULT CALLBACK LowLevelMouseHookProc(int nCode, WPARAM wParam, LPARAM lParam);
    friend LRESULT CALLBACK LowLevelkeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam);
private:
    static GlobalWindowInput *instance;

    MouseLowLevelHandler& mouseLL;
    KeyboardLowLevelHandler& keyboardLL;
    
    GlobalWindowInput(MouseLowLevelHandler &mouseLL, KeyboardLowLevelHandler &keyboardLL);
protected:
    HHOOK keyboardHook;
    HHOOK mouseHook;
public:
    static void Init(MouseLowLevelHandler &mouseLL, KeyboardLowLevelHandler &keyboardLL);
    static void Dispose();

    ~GlobalWindowInput() noexcept;
};


