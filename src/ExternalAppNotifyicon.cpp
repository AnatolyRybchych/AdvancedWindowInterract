#include "ExternalAppNotifyicon.hpp"

#define NOT_NULL(a, b) ((a) != 0 ? (a) : (b)) 


void ExternalAppNotifyicon::NotifyiconProc(WPARAM wParam, LPARAM lParam) noexcept{
    switch (lParam)
    {
    case WM_LBUTTONUP:
        if(IsWindowVisible(GetExternalHWnd())){
            ShowWindow(GetExternalHWnd(), SW_HIDE);
        }
        else{
            ShowWindow(GetExternalHWnd(), SW_SHOW);
            SetWindowPos(GetExternalHWnd(), HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
        }
        break;
    }

    if(IsWindow(GetExternalHWnd()) == false)
        Hide();
}

void ExternalAppNotifyicon::OnCommand(WPARAM wParam) noexcept{
    
}


ExternalAppNotifyicon::ExternalAppNotifyicon(HINSTANCE hInstance, HWND externalWindow)
    :Notifyicon(hInstance){
    externalHWnd = externalWindow;

    visible = true;

    wchar_t title[100];
    int titleLen = GetWindowText(GetExternalHWnd(), title, 100);

    HICON icon = (HICON)SendMessage(GetExternalHWnd(), WM_GETICON, ICON_BIG,LPARAM(0));
    HICON icon2 = (HICON)GetClassLongPtr(GetExternalHWnd(), GCLP_HICON);
    HICON iconSm = (HICON)SendMessage(GetExternalHWnd(), WM_GETICON, ICON_SMALL, LPARAM(0));
    HICON iconSm2 = (HICON)GetClassLongPtr(GetExternalHWnd(), GCLP_HICONSM);

    SetIcon(NOT_NULL(icon, NOT_NULL(icon2, NOT_NULL(iconSm, NOT_NULL(iconSm2, LoadIcon(NULL, IDI_WINLOGO))))));
    SetInfo(title);
}

HWND ExternalAppNotifyicon::GetExternalHWnd() const noexcept{
    return externalHWnd;
}

bool ExternalAppNotifyicon::IsVisible() const noexcept{
    return visible;
}

ExternalAppNotifyicon::~ExternalAppNotifyicon() noexcept{
}
