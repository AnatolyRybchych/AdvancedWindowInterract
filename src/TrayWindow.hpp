#pragma once

#include "Window.hpp"

class TrayWindow: private Window{
private:
    static int counter;
    static constexpr UINT TrayMessage = WM_USER + 1;
    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept override final;

    HICON icon;
protected:
    virtual void NotifyiconProc(WPARAM wParam, LPARAM lParam) noexcept = 0;
public:
    void SetIcon(HICON icon) const noexcept;
    void SetInfo(std::wstring info) const noexcept;
    void Show() const noexcept;
    void Hide() const noexcept;
    TrayWindow(HINSTANCE hInstance);
    virtual ~TrayWindow();
};