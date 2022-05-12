#pragma once

#include "Window.hpp"
#include "WindowParams.hpp"

class MainWindow: public Window{
private:
    WindowParams *windowOverParams;
protected:
    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept override;
    void InspectWindowOver(HWND over) noexcept;
    void DefineWindowView() noexcept;
public:
    void Show(HWND over) noexcept;
    void Hide() const noexcept;
    MainWindow(HINSTANCE hInstance);
};
