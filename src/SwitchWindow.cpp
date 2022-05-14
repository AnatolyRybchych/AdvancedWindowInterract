#include "SwitchWindow.hpp"

int SwitchWindow::counter = 0;

LRESULT SwitchWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
    switch(msg){
    case WM_PAINT:{
        RECT client = GetClientRect();

        PAINTSTRUCT ps;
        Gdiplus::Graphics wndG(BeginPaint(hWnd, &ps));
        Gdiplus::Bitmap buffer(client.right, client.bottom);
        
        Gdiplus::Graphics g(&buffer);
        OnPaint(g);
        wndG.DrawImage(&buffer, Gdiplus::Rect(0, 0, client.right, client.bottom));
        
        EndPaint(hWnd, &ps);
    } return 0;
    case WM_LBUTTONDOWN:
        OnMouseDown();
     return 0;
    case WM_TIMER:
        OnTimer();
    return 0;
    case WM_LBUTTONUP:
        OnMouseUp();
     return 0;
    case WM_ERASEBKGND: return true;
    case WM_MOUSEMOVE:{
        TRACKMOUSEEVENT tme{
            .cbSize = sizeof(TRACKMOUSEEVENT),
            .dwFlags = TME_HOVER | TME_LEAVE,
            .hwndTrack = hWnd,
            .dwHoverTime = 1,
        };
        TrackMouseEvent(&tme);
        OnMouseMove();
    } return 0;
    case WM_MOUSEHOVER:
        OnMouseEnter();
        return 0;
    case WM_MOUSELEAVE:
        OnMouseLeave();
        return 0;
    case WM_DESTROY:
        return 0;
    default:
        return DefWindowProc(hWnd, msg,wParam, lParam);
    }
}

void SwitchWindow::OnPaint(Gdiplus::Graphics &g) noexcept{
    g.SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);

    Gdiplus::SolidBrush *bg;
    Gdiplus::SolidBrush *bgTrigger;
    Gdiplus::SolidBrush *bgSw;
    Gdiplus::Pen *fg;
    RECT client = GetClientRect();
    RECT swBounds = GetSwitchBounds(client);

    if(isMouseDown){
        bg = new Gdiplus::SolidBrush(RGBHEX(0x050505));
        bgSw = new Gdiplus::SolidBrush(RGBHEX(0x000000));
        fg = new Gdiplus::Pen(RGBHEX(0xaaaaff), 2.0f);
    }
    else if(isMouseOver){
        bg = new Gdiplus::SolidBrush(RGBHEX(0x050505));
        bgSw = new Gdiplus::SolidBrush(RGBHEX(0x000000));
        fg = new Gdiplus::Pen(RGBHEX(0xaaaaaa), 2.0f);
    }
    else{
        bg = new Gdiplus::SolidBrush(RGBHEX(0x353535));
        bgSw = new Gdiplus::SolidBrush(RGBHEX(0x252525));
        fg = new Gdiplus::Pen(RGBHEX(0xaaaaaa), 2.0f);
    }

    if(isAnimation) bgTrigger = new Gdiplus::SolidBrush(RGBHEX(0xaaaaff));
    else bgTrigger = bg->Clone();

    g.FillRectangle(bg, Gdiplus::Rect(client.left, client.top, client.right, client.bottom));

    {//draw text
        wchar_t text[100];
        int textLen = GetWindowText(GetHWnd(), text, 100);
        Gdiplus::StringFormat fmt;
        fmt.SetAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
        fmt.SetLineAlignment(Gdiplus::StringAlignment::StringAlignmentCenter);
        Gdiplus::FontFamily family(L"Arial");
        Gdiplus::Font font(&family, 14);
        Gdiplus::SolidBrush textColor(RGBHEX(0xaaaaff));
        g.DrawString(text, textLen, &font, Gdiplus::RectF(0, 0, client.right, client.bottom / 2), &fmt, &textColor);
    }

    DrawSwitchBorder(g, bgSw, fg, swBounds);
    DrawSwitchTrigger(g, bgTrigger, fg, swBounds, progress);

    delete bg;
    delete fg;
    delete bgTrigger;
}

void SwitchWindow::OnMouseMove() noexcept{

}

void SwitchWindow::OnMouseEnter() noexcept{
    if(isMouseOver == false){
        isMouseOver = true;
        InvalidateRect(GetHWnd(), nullptr, true);
    }
}

void SwitchWindow::OnMouseLeave() noexcept{
    if(isMouseDown || isMouseOver){
        isMouseOver = false;
        isMouseDown = false;
        InvalidateRect(GetHWnd(), nullptr, true);
    }
}

void SwitchWindow::OnMouseDown() noexcept{
    if(isMouseDown == false){
            isMouseDown = true;
            if(isAnimation == false){
                isAnimation = true;
                OnSwitch(!switchStatus);
                SetTimer(GetHWnd(), 0, 20, nullptr);
            }
            InvalidateRect(GetHWnd(), nullptr, true);
        }
}

void SwitchWindow::OnMouseUp() noexcept{
    if(isMouseDown){
        isMouseDown = false;
        InvalidateRect(GetHWnd(), nullptr, true);
    }
}

void SwitchWindow::OnTimer() noexcept{
    if(switchStatus)
        progress += 0.1;
    else
        progress -= 0.1;
    
    if(progress < 0){
        progress = 0;
        isAnimation = false;
    }
    if(progress > 1){
        progress = 1;
        isAnimation = false;
    }
    if(isAnimation == false)
        KillTimer(GetHWnd(), 0);
    InvalidateRect(GetHWnd(), nullptr, true);
}


RECT SwitchWindow::GetClientRect() const noexcept{
    RECT res;
    return ::GetClientRect(GetHWnd(), &res), res;
}

RECT SwitchWindow::GetSwitchBounds(const RECT &client) const noexcept{
    return (RECT){
        .left = client.left,
        .top = client.bottom / 2,
        .right = client.right,
        .bottom = client.bottom
    };
}

void SwitchWindow::DrawSwitchTrigger(Gdiplus::Graphics &g, const Gdiplus::Brush *b, const Gdiplus::Pen *p, const RECT &bounds, float progress) const noexcept{
    int border = 0;
    if(p != nullptr) border = p->GetWidth();
    Gdiplus::GraphicsPath path;
    int height = (bounds.bottom - bounds.top - border);
    path.AddEllipse(bounds.left + (int)((bounds.right - bounds.left - height - border) * progress), bounds.top, height, height);

    if(b != nullptr)
        g.FillPath(b, &path);
    if(p != nullptr)
        g.DrawPath(p, &path);
}

void SwitchWindow::DrawSwitchBorder(Gdiplus::Graphics &g, const Gdiplus::Brush *b, const Gdiplus::Pen *p, const RECT &bounds) const noexcept{
    int border = 0;
    if(p != nullptr) border = p->GetWidth();
    int d = bounds.bottom - bounds.top - border;

    Gdiplus::GraphicsPath path;
    

    path.AddBezier(
        Gdiplus::Point(bounds.left + d / 2, bounds.bottom - border),
        Gdiplus::Point(bounds.left + d / 4, bounds.bottom - border),
        Gdiplus::Point(bounds.left, bounds.top + d * 3 / 4),
        Gdiplus::Point(bounds.left, bounds.top + d / 2)
    );
    path.AddBezier(
        Gdiplus::Point(bounds.left, bounds.top + d / 2),
        Gdiplus::Point(bounds.left, bounds.top + d / 4),
        Gdiplus::Point(bounds.left + d / 4, bounds.top),
        Gdiplus::Point(bounds.left + d / 2, bounds.top)
    );
    path.AddBezier(
        Gdiplus::Point(bounds.left + d * 3 / 2, bounds.top),
        Gdiplus::Point(bounds.right - border - d / 4, bounds.top),
        Gdiplus::Point(bounds.right - border, bounds.top + d / 4),
        Gdiplus::Point(bounds.right - border, bounds.top + d / 2)
    );
    path.AddBezier(
        Gdiplus::Point(bounds.right - border, bounds.top + d / 2),
        Gdiplus::Point(bounds.right - border, bounds.bottom - d / 4 - border),
        Gdiplus::Point(bounds.right - border - d / 4, bounds.bottom - border),
        Gdiplus::Point(bounds.right - border - d / 2, bounds.bottom - border)
    );
    path.CloseFigure();

    if(b != nullptr)
        g.FillPath(b, &path);
    if(p != nullptr)
        g.DrawPath(p, &path);
}

SwitchWindow::SwitchWindow(HINSTANCE hInstance, int x, int y, int width, int height, std::wstring title, HWND parent)
    :Window(hInstance, std::wstring() + L"SwWnd_" = std::to_wstring(counter++), title, x, y, width, height, WS_CHILD, parent, 0){
}

void SwitchWindow::OnSwitch(bool status) noexcept{
    if(switchStatus == status) return;
    
    switchStatus = status;
    for(auto switchHandler:switchHandlers)
        if(switchHandler != 0) switchHandler(status);
}

void SwitchWindow::AddOnSwitchHandler(std::function<void(bool)> onSwitch) noexcept{
    switchHandlers.push_back(onSwitch);
}

void SwitchWindow::RemoveOnSwitchHandler(std::function<void(bool)> onSwitch) noexcept{
    //switchHandlers.erase(std::find(switchHandlers.begin(), switchHandlers.end(), onSwitch));
}

bool SwitchWindow::GetSwitchStatus() const noexcept{
    return switchStatus;
}

SwitchWindow::~SwitchWindow(){
}