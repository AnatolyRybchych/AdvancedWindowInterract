#pragma once

#include <vector>
#include <algorithm>
#include "Notifyicon.hpp"


class ExternalAppNotifyicon: public Notifyicon{
private:
    HWND externalHWnd;
    bool visible;
protected:
    void NotifyiconProc(WPARAM wParam, LPARAM lParam) noexcept override;
    void OnCommand(WPARAM wParam) noexcept override;
    //virtual LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept override;
public:
    ExternalAppNotifyicon(HINSTANCE hInstance, HWND externalWindow);
    HWND GetExternalHWnd() const noexcept;
    bool IsVisible() const noexcept;
    ~ExternalAppNotifyicon() noexcept;
};