#include "SwichWindow.hpp"

int SwitchWindow::counter = 0;

LRESULT SwitchWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{

    return DefWindowProc(hWnd, msg,wParam, lParam);
}

SwitchWindow::SwitchWindow(HINSTANCE hInstance, int x, int y, std::wstring title, HWND parent)
    :Window(hInstance, std::wstring() + L"SwWnd_" = std::to_wstring(counter++), title, x, y, 0, 0, WS_CHILD | WS_VISIBLE, parent, WS_EX_LAYERED){

}

void SwitchWindow::OnSwitch(bool status) noexcept{
    for(auto switchHandler:switchHandlers)
        if(switchHandler != 0) switchHandler(status);
}

void SwitchWindow::AddOnSwitchHandler(std::function<void(bool)> onSwitch) noexcept{
    switchHandlers.push_back(onSwitch);
}

void SwitchWindow::RemoveOnSwitchHandler(std::function<void(bool)> onSwitch) noexcept{
    switchHandlers.erase(std::find(switchHandlers.begin(), switchHandlers.end(), onSwitch));
}

SwitchWindow::~SwitchWindow(){

}