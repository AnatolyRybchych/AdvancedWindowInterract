#include "GlobalWindowInput.hpp"

GlobalWindowInput *GlobalWindowInput::instance = nullptr;


LRESULT CALLBACK LowLevelMouseHookProc(int nCode, WPARAM wParam, LPARAM lParam){
    if(nCode < 0) 
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    else
        if(GlobalWindowInput::instance->mouseLL.OnMouseHookLL((MouseMessages)wParam, (MSLLHOOKSTRUCT*)lParam) == false) return 0;
        
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK LowLevelkeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam){
    if(nCode < 0) 
        return CallNextHookEx(NULL, nCode, wParam, lParam);
    else
        GlobalWindowInput::instance->keyboardLL.OnKeyboardHookLL((KeyboardMessages)wParam, (KBDLLHOOKSTRUCT*)lParam);
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

GlobalWindowInput::GlobalWindowInput(MouseLowLevelHandler& mouseLL, KeyboardLowLevelHandler &keyboardLL):mouseLL(mouseLL), keyboardLL(keyboardLL){
    mouseHook = SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseHookProc, NULL, 0);
    if(mouseHook == nullptr)
        throw std::runtime_error("cannot register WH_MOUSE_LL");
    
    mouseHook = SetWindowsHookEx(WH_KEYBOARD_LL, LowLevelkeyboardHookProc, NULL, 0);
    if(mouseHook == nullptr)
        throw std::runtime_error("cannot register WH_KEYBOARD_LL");
}

void GlobalWindowInput::Init(MouseLowLevelHandler &mouseLL, KeyboardLowLevelHandler &keyboardLL){
    if(instance == nullptr)
        instance = new GlobalWindowInput(mouseLL, keyboardLL);
    else
        throw std::logic_error("InputManager is already initialized");
}

void GlobalWindowInput::Dispose(){
    if(instance == nullptr)
        std::logic_error("InputManager is not initialized");
    
    delete instance;
    instance = nullptr;
}

GlobalWindowInput::~GlobalWindowInput() noexcept{
    UnhookWindowsHookEx(mouseHook);
}


