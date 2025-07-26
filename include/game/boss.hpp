//
// Created by donghao on 25-7-2.
//
#ifndef BOSS_HPP
#define BOSS_HPP
#include "hitbox.hpp"

namespace game {
    class Boss {
    public:
        Boss(const float x,const float y,const float hitboxWidth,const float hitboxHeight,const double health)
            :m_x(x),m_y(y),m_hitbox(x,y,hitboxWidth,hitboxHeight),m_health(health) {}
    private:
        float m_x;
        float m_y;
        Hitbox m_hitbox;
        double m_health;
    };
} // game

#endif //BOSS_HPP
