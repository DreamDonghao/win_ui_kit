//
// Created by donghao on 25-7-2.
//
#ifndef BOSS_HPP
#define BOSS_HPP
#include "hitbox.hpp"
#include <co.hpp>
#include <tool.hpp>

namespace game {
    class Boss {
    public:
        Boss(const float x, const float y, const float hitboxWidth, const float hitboxHeight, const double health)
            : m_x(x), m_y(y), m_hitbox(x, y, hitboxWidth, hitboxHeight), m_health(health) {
        }

        void move() {
            m_x += m_speed * cosf(m_moveAngle);
            m_y += m_speed * sinf(m_moveAngle);
        }
        float getX()const {
            return m_x;
        }
        float getY()const {
            return m_y;
        }
        sfui::Task<void> update(float &playerX, float &playerY) {
            while (true) {
                while (distance(m_x, m_y, playerX, playerY) < 1000) {
                    m_x += m_speed * cosf(get_angle_radians(m_x, m_y, playerX, playerY));
                    m_y += m_speed * sinf(get_angle_radians(m_x, m_y, playerX, playerY));
                    co_await std::suspend_always{};
                }
                while (distance(m_x, m_y, playerX, playerY) >= 1000) {
                    co_await std::suspend_always{};
                }
            }
            co_return;
        }

    private:
        float m_x;
        float m_y;
        float m_speed{21};
        float m_moveAngle;
        Hitbox m_hitbox;
        double m_health;
        int state{0};
    };
} // game

#endif //BOSS_HPP
