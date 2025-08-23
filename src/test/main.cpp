// TIP
// Created by donghao on 25-6-12.
// TIP

#include <Window.hpp>
#include <TestPage.hpp>
#include <windows.h>
#include <filesystem>
#include <tkl.hpp>
#include <timepiece.hpp>
//#include <box2d.h>
constexpr int width = 16;
constexpr int heigth = 10;
constexpr int ratio = 100;




#define TEST








int main() {
//#define TEST

#ifdef TEST
    sfui::Window window(width * ratio, heigth * ratio, sfui::WindowState::Windowed);
    window.init(165, false);
    window.addPage(sfui::strToWstr("铁傀儡机"),sfui::makePage<game::TklPage>(&window));
    window.addPage(sfui::strToWstr("主界面"), sfui::makePage<game::MainMenuPage>(&window));
    window.startShow(sfui::strToWstr("主界面"));
#endif
    return 0;
}
