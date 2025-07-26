#pragma once

#include <Page.hpp>
#include <Circle.hpp>
#include <ParticleBuilder.hpp>
#include <thread>
#include <iostream>
#include <player.hpp>
#include <bullet.hpp>
#include <text.hpp>

#include "playerWithCircle.hpp"

namespace game {
    class MainMenuPage : public sfui::Page {
    private:
        sfui::TextureItem mainPage;

        sfui::TextBox textBox;
        sf::String str;
        //sfui::InputBox inputbox;

        float angle = 0;


        game::Player<sfui::Circle> player;

        game::Barrage barrage;
        sfui::TimeIntervalMs timeInterval;

    public:
        explicit MainMenuPage(sfui::Window *p_window)
            : Page(p_window),
              textBox(0, 0, 100, sf::Color::White,
                      R"(zh-cn.ttf)",
                      "hello"),
              player(-300.f, 0.f, 100.f, 100.f, 3.f, 1.f, 50.f, 1.f, 50, sf::Color::Yellow) {
        }

        // 初始化界面元素
        void init() override {
            m_ratio = 0.5;
            //std::println("{}", m_ratio);
        }


        //
        void updateByMessage() override {
            //textBox.setTestString(str);
            //inputbox.run(mp_window->getEvent());

            activeMap(sfui::Key::W, [&]() { player.moveUp(); });
            activeMap(sfui::Key::S, [&]() { player.moveDown(); });
            activeMap(sfui::Key::A, [&]() { player.moveLift(); });
            activeMap(sfui::Key::D, [&]() { player.moveRight(); });
        }

        // 执行界面逻辑
        //sfui::TimeIntervalMs a;

        void update() override {
            //std::cout<<a.elapsed()<<std::endl;

            //inputbox.updateCursor();
            //particle.run();
            // particle.setX(m_mouse.getViewPosition().x);
            // particle.setY(m_mouse.getViewPosition().y);

            using namespace std::chrono;

            constexpr auto period = 16ms; // 每 16ms 一次 ≈ 60 FPS
            const auto start = std::chrono::steady_clock::now();

            // ... 你的逻辑代码，比如更新粒子、处理输入、渲染等 ...

            // 计算本次逻辑花了多少时间
            const auto end = std::chrono::steady_clock::now();

            if (const auto elapsed = end - start; elapsed < period) {
                std::this_thread::sleep_for(period - elapsed); // 等剩下的时间
            } else {
                std::cout << "Warning: Frame over time budget: "
                        << duration_cast<milliseconds>(elapsed).count()
                        << "ms\n";
            }
            setViewCenter(player.getX(), player.getY());
            // angle+=0.05;
            //particle.setX(player.getX());
            //particle.setY(player.getY());

            const game::Player tempPlayer(m_mouse.getViewPosition().x, m_mouse.getViewPosition().y, 6, 6, 1, 1);


            barrage.addBullet(0, 0, 2, static_cast<float>(randomDouble(0, 2 * 3.31415926)), 50, 50, 1);
            barrage.run();

            player.changeHealth(-1 * barrage.dealDamage(player.getHitbox()));
            textBox.setTestString(
                std::string("HP:") + std::to_string(player.getHealth()) + "\ntime:" + std::to_string(
                    timeInterval.elapsed() / 1000) + "s");
        }

        // 渲染页面内容到窗口
        void render() override {
            drawForWindow();

            mp_window->getSfRenderWindow().draw(textBox.getSprite());
            //particle.drow(mp_window->getSfRenderWindow());

            drawForView(
                player,
                player.getHitbox(),
                barrage
            );
            barrage.drowHitbox(mp_window->getSfRenderWindow());
        }
    };
}
