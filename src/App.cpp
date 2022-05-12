#include "App.hpp"

App::App(HINSTANCE hInstance) :appNotifyicon(hInstance){
    this->hInstance = hInstance;
    isAltDown = false;
}

int App::Run(){
    GlobalWindowInput::Init(*this, *this);
    appNotifyicon.SetIcon(LoadIcon(NULL, IDI_APPLICATION));
    

    int exitCode = StartWindowLoop();


    GlobalWindowInput::Dispose();
    return exitCode;
}

int App::StartWindowLoop(){
    MSG msg;
    while (GetMessage(&msg, 0, 0, 0)){
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

bool App::OnKeyDown(KBDLLHOOKSTRUCT *args){
        switch (args->vkCode)
        {
        case VK_MENU:
        case VK_LMENU:
            isAltDown = true;
            break;
        }
        return true;
    }


bool App::OnKeyUp(KBDLLHOOKSTRUCT *args){
        switch (args->vkCode)
        {
        case VK_MENU:
        case VK_LMENU:
            isAltDown = false;
            break;
        }
        return false;
    }

bool App::OnMouseHookLL(MouseMessages message, MSLLHOOKSTRUCT *args) noexcept{
        if(message == MouseMessages::RightUp && isAltDown);
        return true;
    }

bool App::OnKeyboardHookLL(KeyboardMessages message, KBDLLHOOKSTRUCT *args) noexcept{
        if(message == KeyboardMessages::KeyDown || message == KeyboardMessages::SysKeyDown)
            return OnKeyDown(args);
        else if(message == KeyboardMessages::KeyUp || message == KeyboardMessages::SysKeyUp)
            return OnKeyUp(args);
        return true;
    }