#pragma once

#include <Page.hpp>
#include <Circle.hpp>
#include <ParticleBuilder.hpp>
#include <thread>
#include <iostream>
#include <player.hpp>
#include <bullet.hpp>
#include <boss.hpp>

#include "test/boss_a.hpp"
#include <progressBar.hpp>

namespace game {
    class MainMenuPage : public sfui::Page {
    private:
        sfui::TextureItem mainPage;
        sfui::TextBox textBox;
        sf::String str;
        float angle = 0;
        game::Player<sfui::Circle> player;
        float playerX{0}, playerY{0};
        //game::Barrage barrage;
        sfui::TimeIntervalMs timeInterval;
        sfui::TimeIntervalMs abt;
        game::Boss_a boss;
        sfui::Task<void> bossUpdate;
        sfui::Circle circle;
        game::Barrage barrage;
        game::Barrage myBarrage;

        sfui::ProgressBar bossHealthBar;
        sfui::ProgressBar playerHealthBar;
        sfui::TimeIntervalMs time;

    public:
        explicit MainMenuPage(sfui::Window *p_window)
            : Page(p_window),
              textBox(0, 0, 100, sf::Color::White,
                      R"(zh-cn.ttf)",
                      "hello"),
              player(-300.f, 0.f, 50.f, 50.f, 5.f, 100, 50.f, 1.f, 25, sf::Color::Yellow),

              boss(1000, 1000, 100, 100, 10000),
              bossUpdate(boss.update(barrage, myBarrage, playerX, playerY)),
              circle(0, 0, 100, sf::Color::White),
              bossHealthBar(800, 50, 800, 30, 10000, 10000),
              playerHealthBar(200, 30, 100, 20, 100, 100) {
        }

        // 初始化界面元素
        void init() override {
            m_ratio = 0.5;
            //std::println("{}", m_ratio);
            //textBox.setTestString(str);
            activeMap(sfui::Key::W, [&]() { player.moveUp(); });
            activeMap(sfui::Key::S, [&]() { player.moveDown(); });
            activeMap(sfui::Key::A, [&]() { player.moveLift(); });
            activeMap(sfui::Key::D, [&]() { player.moveRight(); });
        }


        //
        void updateByMessage() override {
            //inputBox.run(mp_window->getEvent());
        }


        void update() override {
            bossHealthBar.updateCurrentValue(boss.getHealth());
            playerHealthBar.updateCurrentValue(player.getHealth());
            playerX = player.getX();
            playerY = player.getY();
            boss.turnTo(player.getX(), player.getY());
            bossUpdate.resume();
            circle.setPosition(boss.getX(), boss.getY());
            if (abt.elapsed() > 100) {
                //std::cout<<boss.getHealth()<<std::endl;
                abt.reset();
                if (m_mouse.isLeftPressed()) {
                    myBarrage.addBullet(
                        player.getX(), player.getY(), 30,
                        get_angle_radians(player.getX(), player.getY(), m_mouse.getViewPosition().x,
                                          m_mouse.getViewPosition().y),
                        3, 3, 15
                    );
                }
            }
            barrage.run();
            myBarrage.run();

            //std::cout<<boss.getHitbox().getX()<<" "<<boss.getHitbox().getY()<<std::endl;
            player.changeHealth(-barrage.dealDamage(player.getHitbox()));
            using namespace std::chrono;

            constexpr auto period = 8ms; // 每 16ms 一次 ≈ 60 FPS
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

            if (isCollide(player.getHitbox(), boss.getHitbox())) {
                player.changeHealth(-5);
            }

            const game::Player tempPlayer(m_mouse.getViewPosition().x, m_mouse.getViewPosition().y, 6, 6, 1, 1);

            textBox.setTestString(
                std::string("HP:") + std::to_string(static_cast<int>(player.getHealth())) + "\ntime:" + std::to_string(
                    timeInterval.elapsed() / 1000) + "s\n" + std::string("bossHP:") + std::to_string(
                    static_cast<int>(boss.getHealth())));
        }

        // 渲染页面内容到窗口
        void render() override {
            drawForWindow(
                bossHealthBar,
                playerHealthBar
            );

            drawForView(
                player,
                boss,
                barrage,
                myBarrage
            );
        }
    };
}
