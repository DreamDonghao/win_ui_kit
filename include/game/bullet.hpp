//
// Created by donghao on 25-7-2.
//
#ifndef BULLET_HPP
#define BULLET_HPP
#include <hitbox.hpp>

namespace game {
    class Bullet {
    public:
        Bullet(const float x, const float y, const float speed, const float moveAngle,
               const float hitboxWidth, const float hitboxHeight, const double attack)
            : m_x(x), m_y(y), m_speed(speed), m_moveAngle(moveAngle),
              m_hitbox(x, y, hitboxWidth, hitboxHeight), m_attack(attack) {
        }

        void move() {
            --m_existFrame;
            if (m_existFrame == 0) {
                m_isAlive = false;
            }
            m_x += m_speed * cosf(m_moveAngle);
            m_y += m_speed * sinf(m_moveAngle);
            m_hitbox.setPosition(m_x, m_y);
        }

        [[nodiscard]] float getX() const {
            return m_x;
        }

        [[nodiscard]] float getY() const {
            return m_y;
        }

        [[nodiscard]] Hitbox getHitbox() const {
            return m_hitbox;
        }

        [[nodiscard]] double getAttack()const{
            return m_attack;
        }

        void setAlive(const bool alive) {
            m_isAlive = alive;
        }

        [[nodiscard]] bool isAlive()const {
            return m_isAlive;
        }

        void draw(sf::RenderWindow &window)const {
            const sfui::Circle circle(m_x,m_y,25,sf::Color::Red);
            circle.draw(window);
        }

        void drawHitbox(sf::RenderWindow &window)const{
            m_hitbox.draw(window);
        }

    private:
        float m_x;
        float m_y;
        float m_speed;
        float m_moveAngle;
        Hitbox m_hitbox;
        double m_attack;
        bool m_isAlive{true};
        int m_existFrame{1000};
    };

    class Barrage {
    public:
        Barrage() = default;

        void addBullet(const float x, const float y, const float speed, const float moveAngle,
               const float hitboxWidth, const float hitboxHeight, const double attack) {
            m_bullets.emplace_back(x,y,speed,moveAngle,hitboxHeight,hitboxWidth,attack);
        }

        [[nodiscard]] double dealDamage(const Hitbox& hitbox){
            double damage = 0;
            for (auto &bullet: m_bullets) {
                if (isCollide(hitbox,bullet.getHitbox())) {
                    damage+=bullet.getAttack();
                    bullet.setAlive(false);
                }
            }
            return damage;
        }

        void run() {
            for (size_t i = 0;i <m_bullets.size();) {
                m_bullets[i].move();
                if (!m_bullets[i].isAlive()) {
                    m_bullets[i] = m_bullets.back();
                    m_bullets.pop_back();

                }else {
                    ++i;
                }
            }
        }

        void setIsDrawHitbox(const bool drawHitbox) {
            m_isDrawHitbox = drawHitbox;
        }

        void draw(sf::RenderWindow& window) const{
            for (auto &bullet: m_bullets) {
               bullet.draw(window);
                if (m_isDrawHitbox) {
                    bullet.drawHitbox(window);
                }
            }
        }

    private:
        std::vector<Bullet> m_bullets;
        bool m_isDrawHitbox{false};
    };
} // game

#endif //BULLET_HPP
