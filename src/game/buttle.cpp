//
// Created by donghao on 25-8-20.
//
#include <bullet.hpp>
#include "Circle.hpp"

namespace game {
    Bullet::Bullet(const float x, const float y, const float speed, const float moveAngle, const float hitboxWidth,
                   const float hitboxHeight, const double attack)
        : m_x(x), m_y(y), m_speed(speed), m_moveAngle(moveAngle),
          m_hitbox(x, y, hitboxWidth, hitboxHeight),
          m_attack(attack) {
    }

    void Bullet::move() {
        --m_existFrame;
        if (m_existFrame == 0) {
            m_isAlive = false;
        }
        m_x += m_speed * cosf(m_moveAngle);
        m_y += m_speed * sinf(m_moveAngle);
        m_hitbox.setPosition(m_x, m_y);
    }

    float Bullet::getX() const {
        return m_x;
    }

    float Bullet::getY() const {
        return m_y;
    }

    Hitbox Bullet::getHitbox() const {
        return m_hitbox;
    }

    double Bullet::getAttack() const {
        return m_attack;
    }

    void Bullet::setAlive(const bool alive) {
        m_isAlive = alive;
    }

    bool Bullet::isAlive() const {
        return m_isAlive;
    }

    void Bullet::draw(sf::RenderWindow &window) const {
        const sfui::Circle circle(m_x, m_y, 3, sf::Color::Red);
        circle.draw(window);
    }

    void Bullet::drawHitbox(sf::RenderWindow &window) const {
        m_hitbox.draw(window);
    }

    void Barrage::addBullet(const float x, const float y, const float speed, const float moveAngle,
                            const float hitboxWidth, const float hitboxHeight, const double attack) {
        m_bullets.emplace_back(std::make_unique<Bullet>(
            x, y, speed, moveAngle, hitboxHeight, hitboxWidth, attack
        ));
    }

    // ReSharper disable once CppMemberFunctionMayBeConst
    double Barrage::dealDamage(const Hitbox &hitbox) {
        double damage = 0;
        for (const auto &bullet: m_bullets) {
            if (isCollide(hitbox, bullet->getHitbox())) {
                damage += bullet->getAttack();
                bullet->setAlive(false);
            }
        }
        return damage;
    }

    void Barrage::run() {
        for (size_t i = 0; i < m_bullets.size();) {
            m_bullets[i]->move();
            if (!m_bullets[i]->isAlive()) {
                std::swap(m_bullets[i], m_bullets.back());
                m_bullets.pop_back();
            } else {
                ++i;
            }
        }
    }

    void Barrage::setIsDrawHitbox(const bool drawHitbox) {
        m_isDrawHitbox = drawHitbox;
    }

    void Barrage::draw(sf::RenderWindow &window) const {
        for (auto &bullet: m_bullets) {
            bullet->draw(window);
            if (m_isDrawHitbox) {
                bullet->drawHitbox(window);
            }
        }
    }
}
