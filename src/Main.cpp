
#include "GlobalWindowInput.hpp"

class InputManager : public MouseLowLevelHandler, public KeyboardLowLevelHandler{
public:
    void OnMouseHookLL(MouseMessages message, MSLLHOOKSTRUCT *args) noexcept override{
    }

    void OnKeyboardHookLL(KeyboardMessages message, KBDLLHOOKSTRUCT *args) noexcept override{
        
    }
};



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    InputManager inputManager;
    GlobalWindowInput::Init(inputManager, inputManager);

    MSG msg;
    while (GetMessage(&msg, 0, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    GlobalWindowInput::Dispose();
    return msg.wParam;
}



