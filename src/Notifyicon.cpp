#include "Notifyicon.hpp"

int Notifyicon::counter = 0;

Notifyicon::Notifyicon(HINSTANCE hInstance)
        :Window(hInstance, (std::wstring() + L"NotifyiconWnd" + std::to_wstring(counter++)).c_str(), L"NotifyiconWindow_(should be hidden)", 0, 0, 0, 0, WS_POPUPWINDOW){
    NOTIFYICONDATA notifyiconData;
    memset(&notifyiconData, 0, sizeof(notifyiconData));
    notifyiconData.cbSize = sizeof(notifyiconData);
    notifyiconData.hWnd = GetHWnd();
    notifyiconData.uCallbackMessage = TrayMessage;

    notifyiconData.uFlags = NIF_MESSAGE;
    Shell_NotifyIcon(NIM_ADD, &notifyiconData);
}

LRESULT Notifyicon::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
    if(msg == TrayMessage){
        NotifyiconProc(wParam, lParam);
        return 0;
    }
    else
        return DefWindowProc(hWnd, msg, wParam, lParam);
}

void Notifyicon::SetIcon(HICON icon) const noexcept{
    NOTIFYICONDATA notifyiconData;
    memset(&notifyiconData, 0, sizeof(notifyiconData));
    notifyiconData.cbSize = sizeof(notifyiconData);
    notifyiconData.hWnd = GetHWnd();
    notifyiconData.hIcon = icon;

    notifyiconData.uFlags = NIF_ICON;
    Shell_NotifyIcon(NIM_MODIFY, &notifyiconData);
}

void Notifyicon::SetInfo(std::wstring info) const noexcept{
    NOTIFYICONDATA notifyiconData;
    memset(&notifyiconData, 0, sizeof(notifyiconData));
    notifyiconData.cbSize = sizeof(notifyiconData);
    notifyiconData.hWnd = GetHWnd();
    

    if(info.size() >= sizeof(notifyiconData.szTip) / sizeof(wchar_t)){
        memcpy(&notifyiconData.szTip[0], info.data(), sizeof(notifyiconData.szTip) / sizeof(wchar_t) * sizeof(wchar_t));
        notifyiconData.szTip[sizeof(notifyiconData.szTip) / sizeof(wchar_t)] = 0;
    }
    else{
        memcpy(&notifyiconData.szTip[0], info.data(), info.size() * sizeof(wchar_t));
        notifyiconData.szTip[info.size()] = 0;
    }

    notifyiconData.uFlags = NIF_INFO;
    Shell_NotifyIcon(NIM_MODIFY, &notifyiconData);
}

void Notifyicon::Show() const noexcept{
    NOTIFYICONDATA notifyiconData;
    memset(&notifyiconData, 0, sizeof(notifyiconData));
    notifyiconData.cbSize = sizeof(notifyiconData);
    notifyiconData.hWnd = GetHWnd();
    notifyiconData.dwState = NIS_SHAREDICON;
    notifyiconData.dwStateMask = NIS_SHAREDICON | NIS_HIDDEN;

    notifyiconData.uFlags = NIF_STATE;
    Shell_NotifyIcon(NIM_MODIFY, &notifyiconData);
}

void Notifyicon::Hide() const noexcept{
    NOTIFYICONDATA notifyiconData;
    memset(&notifyiconData, 0, sizeof(notifyiconData));
    notifyiconData.cbSize = sizeof(notifyiconData);
    notifyiconData.hWnd = GetHWnd();
    notifyiconData.dwState = NIS_HIDDEN;
    notifyiconData.dwStateMask = NIS_SHAREDICON | NIS_HIDDEN;

    notifyiconData.uFlags = NIF_STATE;
    Shell_NotifyIcon(NIM_MODIFY, &notifyiconData);
}
    

Notifyicon::~Notifyicon(){
    NOTIFYICONDATA notifyiconData;
    memset(&notifyiconData, 0, sizeof(notifyiconData));
    notifyiconData.cbSize = sizeof(notifyiconData);
    notifyiconData.hWnd = GetHWnd();

    Shell_NotifyIcon(NIM_DELETE, &notifyiconData);
}