#pragma once

#include "Window.hpp"

class MainWindow: public Window{
protected:
    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept override;
public:
    MainWindow(HINSTANCE hInstance);
};
