#pragma once
#include "UnicodeWindows.hpp"

class WindowParams{
private:
    HWND hWnd;
public:
    WindowParams(HWND window);

    bool IsTopmost() const noexcept;
    bool IsHideIcon() const noexcept;

    void SetTopmost(bool status) const noexcept;
    void SetHideIcon(bool status) const noexcept;

    UINT GetWS() const noexcept;
    UINT GetWS_EX() const noexcept;
    bool IsSystemWindow() const noexcept;
    HWND GetHWnd() const noexcept;
};