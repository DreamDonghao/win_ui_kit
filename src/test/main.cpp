// TIP
// Created by donghao on 25-6-12.
// TIP

#include <Window.hpp>
#include <TestPage.hpp>
#include <windows.h>
#include <filesystem>
#include <timepiece.hpp>

//#include <box2d.h>
constexpr int width = 16;
constexpr int heigth = 10;
constexpr int ratio = 80;

int main() {
    sfui::Window window(width * ratio, heigth * ratio, sfui::WindowState::Windowed);
    window.init(165, false);
    window.addPage(sfui::strToWstr("主界面"), sfui::makePage<game::MainMenuPage>(&window));
    window.startShow(sfui::strToWstr("主界面"));

    return 0;
}
