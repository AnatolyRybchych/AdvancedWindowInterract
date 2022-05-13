#pragma once

#include "Window.hpp"
#include "WindowParams.hpp"
#include "HorisontalStackPanel.hpp"
#include "SwitchWindow.hpp"

class MainWindow: public Window{
private:
    WindowParams *windowOverParams;
    HorisontalStackPanel content;

    SwitchWindow sw1;
    SwitchWindow sw2;
protected:
    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept override;
    void InspectWindowOver(HWND over) noexcept;
    void DefineWindowView() noexcept;
public:
    void Show(HWND over) noexcept;
    void Hide() const noexcept;
    MainWindow(HINSTANCE hInstance);
};
