#include "ExternalAppNotifyicons.hpp"

ExternalAppNotifyicons::ExternalAppNotifyicons(HINSTANCE hInstnce) noexcept{
    this->hInstance = hInstance;
}

void ExternalAppNotifyicons::Add(HWND targetWindow){
    if(Has(targetWindow) == false)
        notifyicons.push_back(new ExternalAppNotifyicon(hInstance, targetWindow));
}

void ExternalAppNotifyicons::Remove(HWND targetWindow) noexcept{
    std::vector<ExternalAppNotifyicon*>::iterator toRemove = notifyicons.end();
    for(auto n = notifyicons.begin(); n != notifyicons.end(); n++){
        if((*n)->GetExternalHWnd() == targetWindow){
            toRemove = n;
            break;
        }
    }
    if(toRemove != notifyicons.end()){
        notifyicons.erase(toRemove);
        (*toRemove)->Hide();
        delete (*toRemove);
    }
}

bool ExternalAppNotifyicons::Has(HWND targetWindow) const noexcept{
    for(auto n = notifyicons.begin(); n != notifyicons.end(); n++)
        if((*n)->GetExternalHWnd() == targetWindow) return true;

    return false;
}