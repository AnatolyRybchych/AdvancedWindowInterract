#include "App.hpp"

#include "Icon.hpp"

App::App(HINSTANCE hInstance) :appNotifyicon(hInstance), window(hInstance){
    this->hInstance = hInstance;
    isAltDown = false;
}

static HICON CreateAppIcon() noexcept{

    HBITMAP bmp = CreateBitmap(APP_ICON_WIDTH, APP_ICON_HEIGHT, 1, 32, AppIcon);
    HBITMAP bmpMask = CreateBitmap(APP_ICON_WIDTH, APP_ICON_HEIGHT, 1, 1, nullptr);

    ICONINFO ii = {TRUE};
    ii.hbmColor = bmp;
    ii.hbmMask = bmpMask;

    HICON icon= CreateIconIndirect(&ii);

    DeleteObject(bmp);
    DeleteObject(bmpMask);

    return icon;
};

int App::Run(){
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    GlobalWindowInput::Init(*this);
    appNotifyicon.SetIcon(CreateAppIcon());
    int exitCode = StartWindowLoop();

    GlobalWindowInput::Dispose();
    Gdiplus::GdiplusShutdown(gdiplusToken);
    
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
    case VK_LWIN:
    case VK_RWIN:{
        if(isAltDown){   
            POINT cursorPos;
            if(GetCursorPos(&cursorPos)) window.Show(GetAncestor(WindowFromPoint(cursorPos), GA_ROOTOWNER));
        }
    }
    }
    return true;
}


bool App::OnKeyUp(KBDLLHOOKSTRUCT *args){
    switch (args->vkCode)
    {
    case VK_MENU:
    case VK_LMENU:
        isAltDown = false;
        window.Hide();
        break;
    }
    return false;
}


bool App::OnKeyboardHookLL(KeyboardMessages message, KBDLLHOOKSTRUCT *args) noexcept{
    if(message == KeyboardMessages::KeyDown || message == KeyboardMessages::SysKeyDown)
        return OnKeyDown(args);
    else if(message == KeyboardMessages::KeyUp || message == KeyboardMessages::SysKeyUp)
        return OnKeyUp(args);
    return true;
}