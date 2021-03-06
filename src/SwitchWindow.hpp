#pragma once

#include <functional>
#include <algorithm>

#include "vector"
#include "Window.hpp"

#include <gdiplus.h>

#define TO_INT(val) ((int)(val))
#define RGBAHEX(hex) (Gdiplus::Color((TO_INT(hex) & 0xff000000) >> 24 ,(TO_INT(hex) & 0x00ff0000) >> 16, (TO_INT(hex) & 0x0000ff00) >> 8, (TO_INT(hex) & 0x000000ff)))
#define RGBHEX(hex) (Gdiplus::Color((TO_INT(hex) & 0x00ff0000) >> 16, (TO_INT(hex) & 0x0000ff00) >> 8, (TO_INT(hex) & 0x000000ff)))

class SwitchWindow: public Window{
private:
    float progress = 0.0;
    bool isMouseDown = false;
    bool isMouseOver = false;
    bool isAnimation = false;

    bool switchStatus = false;
    static int counter;
    
    std::function<void(bool)> switchHandler;
protected:
    LRESULT WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept override;
    void OnSwitch(bool status) noexcept;

    void OnPaint(Gdiplus::Graphics &g) noexcept;
    void OnMouseMove() noexcept;
    void OnMouseEnter() noexcept;
    void OnMouseLeave() noexcept;
    void OnMouseDown() noexcept;
    void OnMouseUp() noexcept;
    void OnTimer() noexcept;

    void DrawSwitchBorder(Gdiplus::Graphics &g, const Gdiplus::Brush *b, const Gdiplus::Pen *p, const RECT &bounds) const noexcept;
    void DrawSwitchTrigger(Gdiplus::Graphics &g, const Gdiplus::Brush *b, const Gdiplus::Pen *p, const RECT &bounds, float progress) const noexcept;

    RECT GetSwitchBounds(const RECT &client) const noexcept;
    RECT GetClientRect() const noexcept;
public:
    SwitchWindow(HINSTANCE hInstance, int x, int y, int width, int height, std::wstring title, HWND parent);
    void SetSwitchStatus(bool status) noexcept;
    bool GetSwitchStatus() const noexcept;
    void SetOnSwitchHandler(std::function<void(bool)> onSwitch) noexcept;
    void RemoveOnSwitchHandler(std::function<void(bool)> onSwitch) noexcept;
    virtual ~SwitchWindow();
};