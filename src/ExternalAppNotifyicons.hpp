#pragma once


#include <vector>
#include <memory>
#include "ExternalAppNotifyicon.hpp"


class ExternalAppNotifyicons{
private:
    std::vector<ExternalAppNotifyicon*> notifyicons;
    HINSTANCE hInstance;
public:
    ExternalAppNotifyicons(HINSTANCE hInstnce) noexcept;
    void Add(HWND targetWindow);
    void Remove(HWND targetWindow) noexcept;
    bool Has(HWND targetWindow) const noexcept;
};