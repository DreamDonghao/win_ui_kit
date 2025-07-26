//
// Created by donghao on 25-7-1.
//
#ifndef PLAYER_HPP
#define PLAYER_HPP
#include <hitbox.hpp>

namespace game {
    // T必须提供draw函数与setPosition函数

    template<typename T = void>
    class Player {
    public:
        /**
        * @brief 构造函数，T 为 void 时调用
        *
        * @param x 玩家初始横坐标
        * @param y 玩家初始纵坐标
        * @param hitboxWidth 碰撞盒宽度
        * @param hitboxHeight 碰撞盒高度
        * @param speed 玩家移动速度
        * @param health 玩家生命值
        */
        Player(const float x, const float y, const float hitboxWidth, const float hitboxHeight,
               const float speed, const double health) requires (std::is_same_v<T, void>)
            : m_x(x), m_y(y), m_hitbox(x, y, hitboxWidth, hitboxHeight), m_speed(speed), m_health(health) {
        }

        /**
        * @brief 构造函数，T 非 void 时调用，完美转发参数给绘制对象
        *
        * @tparam Args 可变参数模板，传递给绘制对象构造函数
        * @param x 玩家初始横坐标
        * @param y 玩家初始纵坐标
        * @param hitboxWidth 碰撞盒宽度
        * @param hitboxHeight 碰撞盒高度
        * @param speed 玩家移动速度
        * @param health 玩家生命值
        * @param args 转发给绘制对象构造函数的参数包
        */
        template<typename... Args>
        Player(const float x, const float y, const float hitboxWidth, const float hitboxHeight,
               const float speed, const double health, Args &&... args) requires (!std::is_same_v<T, void>)
            : m_x(x), m_y(y), m_hitbox(x, y, hitboxWidth, hitboxHeight), m_speed(speed), m_health(health),
              mp_draw(std::make_unique<T>(std::forward<Args>(args)...)) {
        }

        ~Player() = default;

        void setX(const float x) {
            m_x = x;
            m_hitbox.setPosition(m_x, m_y);
        }

        void setY(const float y) {
            m_y = y;
            m_hitbox.setPosition(m_x, m_y);
        }

        void moveX(const float x) {
            m_x += x;
            m_hitbox.setPosition(m_x, m_y);
        }

        void moveY(const float y) {
            m_y += y;
            m_hitbox.setPosition(m_x, m_y);
        }

        void moveLift() {
            m_x -= m_speed;
            m_hitbox.setPosition(m_x, m_y);
        }

        void moveUp() {
            m_y -= m_speed;
            m_hitbox.setPosition(m_x, m_y);
        }

        void moveRight() {
            m_x += m_speed;
            m_hitbox.setPosition(m_x, m_y);
        }

        void moveDown() {
            m_y += m_speed;
            m_hitbox.setPosition(m_x, m_y);
        }

        [[nodiscard]] float getX() const {
            return m_x;
        }

        [[nodiscard]] float getY() const {
            return m_y;
        }

        void setHealth(const float health) {
            m_health = health;
        }

        void changeHealth(const double health) {
            m_health += health;
        }

        [[nodiscard]] double getHealth() const{
            return m_health;
        }

        [[nodiscard]] Hitbox &getHitbox(){
            return m_hitbox;
        }

        void draw(sf::RenderWindow &window) requires (!std::is_same_v<T, void>) {
            mp_draw->setPosition(m_x, m_y);
            mp_draw->draw(window);
        }

    private:
        using draw_ptr_t = std::conditional_t<std::is_void_v<T>, std::nullptr_t, std::unique_ptr<T>>;
        float m_x;
        float m_y;
        Hitbox m_hitbox;
        float m_speed;
        double m_health;

        draw_ptr_t mp_draw;
    };
} // game

#endif //PLAYER_HPP
