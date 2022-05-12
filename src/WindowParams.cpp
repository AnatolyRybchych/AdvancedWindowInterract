#include "WindowParams.hpp"

WindowParams::WindowParams(HWND window){
    hWnd = window;
    
}

HWND WindowParams::GetHWnd() const noexcept{
    return hWnd;
}

bool WindowParams::IsSystemWindow() const noexcept{
    return isSystemWindow;
}