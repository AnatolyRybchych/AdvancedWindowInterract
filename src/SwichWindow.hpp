#pragma once

#include <functional>
#include <algorithm>

#include "vector"
#include "Window.hpp"

class SwitchWindow: public Window{
private:
    static int counter;
    std::vector<std::function<void(bool)>> switchHandlers;
protected:
    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept override;
    void OnSwitch(bool status) noexcept;
public:
    SwitchWindow(HINSTANCE hInstance, int x, int y, std::wstring title, HWND parent);
    void AddOnSwitchHandler(std::function<void(bool)> onSwitch) noexcept;
    void RemoveOnSwitchHandler(std::function<void(bool)> onSwitch) noexcept;
    virtual ~SwitchWindow();
};