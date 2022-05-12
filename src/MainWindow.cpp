#include "MainWindow.hpp"

MainWindow::MainWindow(HINSTANCE hInstance):Window(hInstance, L"MWCls", L"MainWindow", 0, 0, 120, 30, WS_POPUPWINDOW){

}


LRESULT MainWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
    return DefWindowProc(hWnd, msg, wParam, lParam);
}
