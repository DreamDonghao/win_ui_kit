//
// Created by donghao on 25-8-19.
//
#ifndef BOSS_A_HPP
#define BOSS_A_HPP
#include <boss.hpp>
#include <Circle.hpp>
#include <bullet.hpp>

namespace game {
    class Boss_a : public Boss {
    public:
        Boss_a(const float x, const float y, const float hitboxWidth, const float hitboxHeight, const double health)
            : Boss(x, y, hitboxWidth, hitboxHeight, health) {
        }

        sfui::Task<void> update(Barrage &barrage, Barrage &enemyBarrage, float &playerX, float &playerY) {
            co_await std::suspend_always{};
            double oldHealth = getHealth();
            sfui::TimeIntervalMs t1;
            sfui::TimeIntervalMs t2;
            sfui::TimeIntervalMs t3;
            while (getHealth() > 0) {
                alwaysActive(barrage, enemyBarrage, playerX, playerY, oldHealth);


                t1.reset();
                while (t1.elapsed() < 5000) {
                    alwaysActive(barrage, enemyBarrage, playerX, playerY, oldHealth);
                    co_await std::suspend_always{};
                }


                t2.reset();
                while (t2.elapsed() < 7000) {
                    alwaysActive(barrage, enemyBarrage, playerX, playerY, oldHealth);
                    if (t3.elapsed() > 100) {
                        t3.reset();
                        addBullet(barrage);
                    }
                    co_await std::suspend_always{};
                }

                co_await std::suspend_always{};
            }
            co_return;
        }


        void addBullet(Barrage &barrage) const {
            for (auto &a: abc) {
                barrage.addBullet(a.getX(), a.getY(), 15, get_angle_radians(getX(), getY(), a.getX(), a.getY()),
                                  2, 2, 1);
            }
        }

        void draw(sf::RenderWindow &window) override {
            for (const auto &a: abc) {
                a.draw(window);
            }
        }

    private
    :
        std::vector<sfui::Circle> abc{
            {getX(), getY(), 3, sf::Color::White},
            {getX(), getY(), 3, sf::Color::White}
        };

        sfui::Angle angle{0};

        void alwaysActive(Barrage &barrage, Barrage &enemyBarrage, float &playerX, float &playerY,
                          double &oldHealth) {
            if (oldHealth - getHealth() > 1000) {
                abc.emplace_back(getX(), getY(), 3, sf::Color::White);
                oldHealth = getHealth();
            }
            angle.revolve(0.05);
            for (auto &a: abc) {
                a.setPosition(getX() + 60 * angle.getCos(), getY() + 60 * angle.getSin());
                angle.revolve(2 * sfui::PI / static_cast<float>(abc.size()));
            }

            if (distance(playerX,playerY,getX(),getY())>1000) {
                setSpeed(12.5);

            }else {

                setSpeed(2.5);

            }
            changeHealth(-enemyBarrage.dealDamage(getHitbox()));
            move();
        }
    };
} // game

#endif //BOSS_A_HPP
