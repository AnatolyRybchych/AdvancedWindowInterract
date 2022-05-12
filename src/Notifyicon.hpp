#pragma once

#include "Window.hpp"

class Notifyicon: public Window{
private:
    static int counter;
    static constexpr UINT TrayMessage = WM_USER + 1;

    HICON icon;
protected:
    virtual LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept override;
    virtual void NotifyiconProc(WPARAM wParam, LPARAM lParam) noexcept = 0;
    virtual void OnCommand(WPARAM wParam) noexcept = 0;
public:
    void SetIcon(HICON icon) const noexcept;
    void SetInfo(std::wstring info) const noexcept;
    void Show() const noexcept;
    void Hide() const noexcept;
    Notifyicon(HINSTANCE hInstance);
    virtual ~Notifyicon();
};