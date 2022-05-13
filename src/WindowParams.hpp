#pragma once
#include "UnicodeWindows.hpp"

class WindowParams{
private:
    HWND hWnd;
    bool isSystemWindow;
    UINT windowStyles;
    UINT windowExStyles;
public:
    WindowParams(HWND window);

    UINT GetWS();
    UINT GetWS_EX();
    bool IsSystemWindow() const noexcept;
    HWND GetHWnd() const noexcept;
};