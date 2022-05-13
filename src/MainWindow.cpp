#include "MainWindow.hpp"

MainWindow::MainWindow(HINSTANCE hInstance)
    :Window(hInstance, L"MWCls", L"MainWindow", 0, 0, 120, 30, WS_POPUP, nullptr, WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_LAYERED)
    , content(hInstance, GetHWnd())
    , sw1(hInstance, 0, 0, 100, 100, L"Topmost", content.GetHWnd())
    , sw2(hInstance, 0, 0, 100, 100, L"Hide icon", content.GetHWnd())
{
    windowOverParams = nullptr;

    SetLayeredWindowAttributes(GetHWnd(), 0, 200, LWA_ALPHA);

    ShowWindow(sw1.GetHWnd(), SW_NORMAL);
    ShowWindow(sw2.GetHWnd(), SW_NORMAL);
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

    content.Validate();
}

void MainWindow::Show(HWND over) noexcept{
    InspectWindowOver(over);
    if(windowOverParams == nullptr || windowOverParams->IsSystemWindow()) return;
    
    DefineWindowView();
    
    ShowWindow(GetHWnd(), SW_NORMAL);
}

void MainWindow::Hide() const noexcept{
    ShowWindow(GetHWnd(), SW_HIDE);
}