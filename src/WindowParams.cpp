#include "WindowParams.hpp"

WindowParams::WindowParams(HWND window){
    hWnd = window;
    isSystemWindow = false;

    
    
}

HWND WindowParams::GetHWnd() const noexcept{
    return hWnd;
}

bool WindowParams::IsSystemWindow() const noexcept{
    return isSystemWindow;
}