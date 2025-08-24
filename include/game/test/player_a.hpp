//
// Created by donghao on 25-8-23.
//
#ifndef PLAYER_A_HPP
#define PLAYER_A_HPP
#include "bullet.hpp"
#include "player.hpp"
#include <SFML/Audio.hpp>
namespace game {
    class PlayerBullet : public Bullet {
    public:
        PlayerBullet(const float x, const float y, const float speed, const float moveAngle,
                     const float hitboxWidth, const float hitboxHeight, const double attack, Boss &boss)
            : Bullet(x, y, speed, moveAngle, hitboxWidth, hitboxHeight, attack), m_boss(boss) {
        }

        ~PlayerBullet() override = default;

        void move() override {
            // 归一化到 (-PI, PI]
            auto normalize = [](double rad) {
                while (rad <= -sfui::PI) rad += 2 * sfui::PI;
                while (rad > sfui::PI) rad -= 2 * sfui::PI;
                return rad;
            };

            if (distance(m_boss.getX(), m_boss.getY(), getX(), getY()) < 600) {
                const double angleToBoss = get_angle_radians(getX(), getY(), m_boss.getX(), m_boss.getY());
                const double current = getMoveAngle().getAngleValue();

                if (const double diff = normalize(angleToBoss - current); diff > 0) {
                    turnAngle(0.2); // 朝右转
                } else {
                    turnAngle(-0.2); // 朝左转
                }
            }

            this->Bullet::move();
        }

        void draw(sf::RenderWindow &window) const override {
            const sfui::Circle circle(getX(), getY(), 3, sf::Color::Yellow);
            circle.draw(window);
        }

    private:
        Boss &m_boss;
    };


    class Player_a : public Player {
    public:
        Player_a(const float x, const float y, const float hitboxWidth, const float hitboxHeight,
                 const float speed, const double health)
            : Player(x, y, hitboxWidth, hitboxHeight, speed, health), m_noDodgeSpeed(speed) {
            if (!buffer.loadFromFile("assets/media/a.mp3")) {  // 短音效
                std::cerr << "加载失败\n";
            }
            sound.setBuffer(buffer); // 绑定音频数据
            sound.setVolume(100);     // 音量 0-100
        }

        void dodge() {
            if (dt.elapsed() > 3000) {
                dt.reset();
                m_isDodge = true;
            }
        }

        double getDodgeCooldownTime() const {
            return static_cast<double>(dt.elapsed()) / 1000;
        }

        sfui::Task<void> update(sfui::Mouse &mouse, Barrage &barrage, Barrage &enemyBarrage, Boss &boss) {
            co_await std::suspend_always{};
            sfui::TimeIntervalMs time, t2;
            while (getHealth() > 0) {
                changeHealth(-enemyBarrage.dealDamage(getHitbox()));
                if (m_isDodge) {
                    setSpeed(m_dodgeSpeed);
                    m_isDodge = false;
                    t2.reset();
                }

                if (t2.elapsed() > 50) {
                    setSpeed(m_noDodgeSpeed);
                }

                if (time.elapsed() > 300) {
                    time.reset();
                    if (mouse.isLeftPressed()) {




                        sound.play();            // 播放
                        barrage.addBullet(std::make_unique<PlayerBullet>(
                                getX(), getY(), 30,
                                get_angle_radians(getX(), getY(), mouse.getViewPosition().x,
                                                  mouse.getViewPosition().y),
                                3, 3, 50, boss)
                        );
                    }
                }
                co_await std::suspend_always{};
            }
            co_return;
        }

        void draw(sf::RenderWindow &window) override {
            const sfui::Circle c(getX(), getY(), 25, sf::Color::Yellow);
            c.draw(window);
        }

    private:
        bool m_isDodge{false};
        sfui::TimeIntervalMs dt;
        float m_dodgeSpeed{87};
        float m_noDodgeSpeed;



        sf::SoundBuffer buffer;
        sf::Sound sound;
    };
} // game

#endif //PLAYER_A_HPP
