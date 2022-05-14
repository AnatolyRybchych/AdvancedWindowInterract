#include "WindowParams.hpp"

WindowParams::WindowParams(HWND window){
    hWnd = window;
}


bool WindowParams::IsTopmost() const noexcept{
    return (GetWS_EX() & WS_EX_TOPMOST);
}

bool WindowParams::IsHideIcon() const noexcept{
    return (GetWS_EX() & WS_EX_TOOLWINDOW); 
}

void WindowParams::SetTopmost(bool status) const noexcept{

    if(status) SetWindowPos(GetHWnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    else SetWindowPos(GetHWnd(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void WindowParams::SetHideIcon(bool status) const noexcept{
    

    UINT styles = GetWS_EX();
    if(status)
        styles |= WS_EX_TOOLWINDOW;
    else
        styles &= ~WS_EX_TOOLWINDOW;

    ShowWindow(GetHWnd(), SW_HIDE);
    SetWindowLong(GetHWnd(), GWL_EXSTYLE, styles);
    ShowWindow(GetHWnd(), SW_SHOW);
}

UINT WindowParams::GetWS() const noexcept{
    return (UINT) GetWindowLong(GetHWnd(), GWL_STYLE);
}

UINT WindowParams::GetWS_EX() const noexcept{
    return (UINT) GetWindowLong(GetHWnd(), GWL_EXSTYLE);
}

bool WindowParams::IsSystemWindow() const noexcept{
    return false;
}

HWND WindowParams::GetHWnd() const noexcept{
    return hWnd;
}
