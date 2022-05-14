#include "MainWindow.hpp"

MainWindow::MainWindow(HINSTANCE hInstance)
    :Window(hInstance, L"MWCls", L"MainWindow", 0, 0, 120, 30, WS_POPUP, nullptr, WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_LAYERED)
    , content(hInstance, GetHWnd())
    , swTopmost(hInstance, 0, 0, 100, 100, L"Top most", content.GetHWnd())
    , swHideIcon(hInstance, 0, 0, 100, 100, L"Hide icon", content.GetHWnd())
    , swNotifyicon(hInstance, 0, 0, 100, 100, L"Notifyicon", content.GetHWnd())
    , notifyicons(hInstance)
{
    windowOverParams = nullptr;

    SetLayeredWindowAttributes(GetHWnd(), 0, 200, LWA_ALPHA);

    ShowWindow(swTopmost.GetHWnd(), SW_NORMAL);
    ShowWindow(swHideIcon.GetHWnd(), SW_NORMAL);
    ShowWindow(swNotifyicon.GetHWnd(), SW_NORMAL);

    swTopmost.SetOnSwitchHandler(std::bind(OnSwitchTopmost, this, std::placeholders::_1));
    swHideIcon.SetOnSwitchHandler(std::bind(OnSwitchHideIcon, this, std::placeholders::_1));
    swNotifyicon.SetOnSwitchHandler(std::bind(OnSwitchNotifyicon, this, std::placeholders::_1));
}

void MainWindow::OnSwitchTopmost(bool status) noexcept{
    if(windowOverParams != nullptr){
        windowOverParams->SetTopmost(status);
        SetWindowPos(GetHWnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        swTopmost.SetSwitchStatus(windowOverParams->IsTopmost());
    }
    
}

void MainWindow::OnSwitchHideIcon(bool status) noexcept{
    if(windowOverParams != nullptr){
        windowOverParams->SetHideIcon(status);
        SetWindowPos(GetHWnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);
        swHideIcon.SetSwitchStatus(windowOverParams->IsHideIcon());
    }
}

void MainWindow::OnSwitchNotifyicon(bool status) noexcept{
    if(windowOverParams != nullptr){
        if(status) notifyicons.Add(windowOverParams->GetHWnd());
        else notifyicons.Remove(windowOverParams->GetHWnd());

        swNotifyicon.SetSwitchStatus(notifyicons.Has(windowOverParams->GetHWnd()));
    }
}



LRESULT MainWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
    switch (msg)
    {
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
}

void MainWindow::InspectWindowOver(HWND over) noexcept{
    if(windowOverParams != nullptr) delete windowOverParams,  windowOverParams = nullptr; 

    try
    {
        windowOverParams = new WindowParams(GetAncestor(over, GA_ROOTOWNER));
    }
    catch(const std::exception& e){}
    
}

void MainWindow::DefineWindowView() noexcept{
    RECT wndRect;
    GetWindowRect(windowOverParams->GetHWnd(), &wndRect);
    SetWindowPos(GetHWnd(), HWND_TOPMOST, wndRect.left, wndRect.top, wndRect.right - wndRect.left, wndRect.bottom - wndRect.top, 0);

    swTopmost.SetSwitchStatus(windowOverParams->IsTopmost());
    swHideIcon.SetSwitchStatus(windowOverParams->IsHideIcon());
    swNotifyicon.SetSwitchStatus(notifyicons.Has(windowOverParams->GetHWnd()));

    content.Validate();
}

void MainWindow::Show(HWND over) noexcept{
    if(IsWindowVisible(GetHWnd())) return;
    InspectWindowOver(over);
    if(windowOverParams == nullptr || windowOverParams->IsSystemWindow()) return;

    RECT windowOverRect;
    GetWindowRect(windowOverParams->GetHWnd(), &windowOverRect);

    SIZE contentSize = content.GetContentSize();
    if(windowOverRect.right - windowOverRect.left < contentSize.cx || windowOverRect.bottom - windowOverRect.top < contentSize.cy)
        return;

    DefineWindowView();
    ShowWindow(GetHWnd(), SW_NORMAL);
}

void MainWindow::Hide() const noexcept{
    ShowWindow(GetHWnd(), SW_HIDE);
}