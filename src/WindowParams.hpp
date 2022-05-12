#pragma once
#include "UnicodeWindows.hpp"

class WindowParams{
private:
    HWND hWnd;
    bool isSystemWindow;
public:
    WindowParams(HWND window);

    bool IsSystemWindow() const noexcept;
    HWND GetHWnd() const noexcept;
};