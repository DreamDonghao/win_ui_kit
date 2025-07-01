#pragma once

#include <ComplexPage.hpp>
#include <windows.h>
#include <Circle.hpp>
// #include <elemental.hpp>
// #include <biology.hpp>
// #include <world_elemental.hpp>
// #include <player.hpp>
#include <print>
#include <ParticleBuilder.hpp>
#include <thread>
#include <iostream>

namespace game {
    class MainMenuPage : public sfui::ComplexPage {
    private:
        sfui::TextureItem mainPage;

        sfui::TextBox textBox;
        sf::String str;
        //sfui::InputBox inputbox;

        sfui::ParticleBuilder particle;

        float angle = 0;

    public:
        explicit MainMenuPage(sfui::Window *p_window)
            : ComplexPage(p_window),
              textBox(0, 0, 100, sf::Color::White,
                      R"(C:\Users\donghao\AppData\Local\Programs\cursor\resources\app\out\media\jetbrains-mono-regular.ttf)",
                      "hello"),
              particle(0, 0, 100, 1, std::chrono::milliseconds(5000), std::chrono::milliseconds(1), {0.1, 0.5},
                       sf::Color::White) {
        }

        // 初始化界面元素
        void initializePageElements() override {
            m_ratio = 0.5;
            std::println("{}", m_ratio);
        }

        // 初始化消息-事件映射
        void initMessageBinding() override {
        }


        //
        void updateByMessage() override {
            //textBox.setTestString(str);
            //inputbox.run(mp_window->getEvent());
        }

        // 执行界面逻辑
        //sfui::TimeIntervalMs a;

        void update() override {
            //std::cout<<a.elapsed()<<std::endl;

            //inputbox.updateCursor();
            particle.run();
            // particle.setX(m_mouse.getViewPosition().x);
            // particle.setY(m_mouse.getViewPosition().y);

            using namespace std::chrono;

            constexpr auto period = milliseconds(16); // 每 16ms 一次 ≈ 60 FPS
            const auto start = std::chrono::steady_clock::now();

            // ... 你的逻辑代码，比如更新粒子、处理输入、渲染等 ...

            // 计算本次逻辑花了多少时间
            const auto end = std::chrono::steady_clock::now();

            if (const auto elapsed = end - start; elapsed < period) {
                std::this_thread::sleep_for(period - elapsed); // 等剩下的时间
            } else {
                // 哼，超时啦，当前帧跑太久了喵~
                std::cout << "Warning: Frame over time budget: "
                        << duration_cast<milliseconds>(elapsed).count()
                        << "ms\n";
            }
            setViewCenter(0,0);
            angle+=0.05;
             particle.setX(cos(angle)*100);
             particle.setY(sin(angle)*100);

        }

        // 渲染页面内容到窗口
        void render() override {
            mp_window->getSfRenderWindow().setView(mp_window->getSfRenderWindow().getDefaultView());

            i_updateView();
            particle.drow(mp_window->getSfRenderWindow());
        }

    };
}
