#include "HorisontalStackPanel.hpp"

#define MAX(a,b) ((a) > (b) ? (a) : (b))

int HorisontalStackPanel::counter = 0;

typedef struct{
    SIZE childsRectSize;
    RECT parentRect;
    int currX;
} HSPLocateChildsParams;

static BOOL CALLBACK CalcChildsRectSize(HWND currChild, LPARAM szResult){
    SIZE *result = (SIZE*)szResult;
    RECT currRect;
    GetWindowRect(currChild, &currRect);

    result->cx += currRect.right - currRect.left;
    result->cy = MAX(result->cy, currRect.bottom - currRect.top);
    return TRUE;
}

static BOOL CALLBACK LocateChilds(HWND currChild, LPARAM lParams){
    HSPLocateChildsParams *params = (HSPLocateChildsParams*)lParams;
    RECT currRect;
    GetWindowRect(currChild, &currRect);

    SetWindowPos(
        currChild, nullptr, 
        params->currX, (params->parentRect.bottom- currRect.bottom) / 2,
        0, 0,
        SWP_NOZORDER | SWP_NOSIZE
    );
    params->currX += currRect.right - currRect.left;

    return TRUE;
}

LRESULT HorisontalStackPanel::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
    switch (msg)
    {
    case WM_SIZE:{
        RECT parentRect;
        GetClientRect(GetParent(hWnd), &parentRect);
        SetWindowPos(hWnd, 0, 0, 0, parentRect.right, parentRect.bottom, SWP_NOZORDER);
    }
    case WM_CHILDACTIVATE:{
        HSPLocateChildsParams params;
        GetClientRect(hWnd, &params.parentRect);
        memset(&params, 0, sizeof(params));
        EnumChildWindows(hWnd, CalcChildsRectSize, (LPARAM)&params.childsRectSize);
        params.currX = (params.parentRect.right - params.childsRectSize.cy) / 2;
        EnumChildWindows(hWnd, LocateChilds, (LPARAM)&params);
    }return 0;
    default:
        return DefWindowProc(hWnd, msg, wParam, lParam);
    }
}

HorisontalStackPanel::HorisontalStackPanel(HINSTANCE hInstance, HWND parent) 
    : Window(hInstance, std::wstring() + L"WndHSP_" + std::to_wstring(counter++), L"Horisontal stack panel", 0, 0, 0, 0, WS_CHILD | WS_VISIBLE, parent, WS_EX_LAYERED ){
    
    RECT parentRect;
    GetClientRect(parent, &parentRect);
}