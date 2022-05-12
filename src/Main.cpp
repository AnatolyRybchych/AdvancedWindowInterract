
#include "GlobalWindowInput.hpp"
#include "Window.hpp"
#include "TrayWindow.hpp"

class InputManager : public MouseLowLevelHandler, public KeyboardLowLevelHandler{
public:
    void OnMouseHookLL(MouseMessages message, MSLLHOOKSTRUCT *args) noexcept override{
    }

    void OnKeyboardHookLL(KeyboardMessages message, KBDLLHOOKSTRUCT *args) noexcept override{
        
    }
};

class Tray: public TrayWindow{
protected:
    void NotifyiconProc(WPARAM wParam, LPARAM lParam) noexcept{
        //MessageBox(0, L"", L"", 0);
    }
public:
    Tray(HINSTANCE hInstance):TrayWindow(hInstance){

    }
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    InputManager inputManager;
    //GlobalWindowInput::Init(inputManager, inputManager);

    Tray tray(hInstance);

    tray.SetIcon(LoadIcon(NULL, IDI_QUESTION));

    MSG msg;
    while (GetMessage(&msg, 0, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    //GlobalWindowInput::Dispose();
    return msg.wParam;
}



