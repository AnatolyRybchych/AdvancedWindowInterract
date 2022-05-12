#pragma once

#include "Notifyicon.hpp"

class AppNotifyicon: public Notifyicon{
private:
    HMENU menu;
    static constexpr UINT_PTR MenuItemExit = 1;
protected:
    void NotifyiconProc(WPARAM wParam, LPARAM lParam) noexcept;
    void OnCommand(WPARAM wParam) noexcept override;
public:
    AppNotifyicon(HINSTANCE hInstance);
    ~AppNotifyicon();
};