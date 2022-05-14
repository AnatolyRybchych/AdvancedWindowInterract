#pragma once

#include "Notifyicon.hpp"

class ExternalAppNotifyicon: public Notifyicon{
private:
    HWND externalHWnd;
protected:
    void NotifyiconProc(WPARAM wParam, LPARAM lParam) noexcept override;
    void OnCommand(WPARAM wParam) noexcept override;
public:
    ExternalAppNotifyicon(HINSTANCE hInstance, HWND externalWindow);
    HWND GetExternalHWnd() const noexcept;
    ~ExternalAppNotifyicon() noexcept;
};