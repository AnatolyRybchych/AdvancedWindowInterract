#include "AppNotifyicon.hpp"

void AppNotifyicon::NotifyiconProc(WPARAM wParam, LPARAM lParam) noexcept{
        if(lParam == WM_RBUTTONUP){
            POINT cursorPos;
            SetForegroundWindow(GetHWnd());
            if(GetCursorPos(&cursorPos))
                TrackPopupMenuEx(menu, TPM_BOTTOMALIGN, cursorPos.x, cursorPos.y, GetHWnd(), NULL);
        }
    }

void AppNotifyicon::OnCommand(WPARAM wParam) noexcept{
        if(wParam == MenuItemExit)
            PostQuitMessage(0);
    }

AppNotifyicon::AppNotifyicon(HINSTANCE hInstance):Notifyicon(hInstance){
        menu = CreatePopupMenu();
        HMENU menuItem = CreateMenu();
        AppendMenu(menu, MF_STRING, MenuItemExit, L"Exit");
    }

AppNotifyicon::~AppNotifyicon(){
        DestroyMenu(menu);
    }