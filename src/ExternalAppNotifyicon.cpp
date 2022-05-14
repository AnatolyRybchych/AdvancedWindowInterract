#include "ExteranlAppNotifyicon.hpp"


void ExternalAppNotifyicon::NotifyiconProc(WPARAM wParam, LPARAM lParam) noexcept{
    switch (wParam)
    {
    case WM_LBUTTONUP:
        if(IsWindowVisible(GetExternalHWnd()))
            ShowWindow(GetExternalHWnd(), SW_HIDE);
        else
            ShowWindow(GetExternalHWnd(), SW_NORMAL);
        break;
    }
}

void ExternalAppNotifyicon::OnCommand(WPARAM wParam) noexcept{

}

ExternalAppNotifyicon::ExternalAppNotifyicon(HINSTANCE hInstance, HWND externalWindow)
    :Notifyicon(hInstance){
    externalHWnd = externalWindow;

    //wchar_t title[100];
    //int titleLen = GetWindowText(GetExternalHWnd(), title, 100);
    //SetInfo(title);

    HICON icon = (HICON)SendMessage(GetExternalHWnd(), WM_GETICON, ICON_BIG,LPARAM(0));
    SetIcon(icon);
}

HWND ExternalAppNotifyicon::GetExternalHWnd() const noexcept{
    return externalHWnd;
}

ExternalAppNotifyicon::~ExternalAppNotifyicon() noexcept{
    
}
