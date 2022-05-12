#include "MainWindow.hpp"

MainWindow::MainWindow(HINSTANCE hInstance)
    :Window(hInstance, L"MWCls", L"MainWindow", 0, 0, 120, 30, WS_POPUP, nullptr, WS_EX_LAYERED | WS_EX_TOOLWINDOW | WS_EX_TOPMOST){
    SetLayeredWindowAttributes(GetHWnd(), 0, 100, LWA_ALPHA);
    windowOverParams = nullptr;
}


LRESULT MainWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
    return DefWindowProc(hWnd, msg, wParam, lParam);
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