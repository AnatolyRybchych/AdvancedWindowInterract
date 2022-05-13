#pragma once

#include "Window.hpp"

class HorisontalStackPanel: public Window{
private:
    static int counter;
protected:
    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept override;
public:
    HorisontalStackPanel(HINSTANCE hInstance, HWND parent);
    void Validate() const noexcept;
};