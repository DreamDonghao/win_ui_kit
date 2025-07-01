//
// Created by donghao on 25-6-28.
//
#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"

namespace sfui {
    class Circle {
    public:
        Circle(const float x, const float y, const float radius, const sf::Color fillColor)
            :m_x(x),m_y(y),m_radius(radius),m_fillColor(fillColor){
            circle.setPosition(x-radius,y-radius);
            circle.setRadius(radius);
            circle.setFillColor(fillColor);
        }

        void setX(const float x) {
            m_x = x;
            circle.setPosition(m_x,m_y);
        }

        void setY(const float y) {
            m_y = y;
            circle.setPosition(m_x,m_y);
        }

        void moveX(const float x) {
            m_x +=x;
            circle.setPosition(m_x,m_y);
        }

        void moveY(const float y) {
            m_y +=y;
            circle.setPosition(m_x,m_y);
        }

        float getRadius() const {return m_radius;}
        float getX() const {return m_x;}
        float getY() const {return m_y;}



        void draw(sf::RenderWindow &renderWindow) const {
            renderWindow.draw(circle);
        }

    private:
        sf::CircleShape circle;
        float m_x;
        float m_y;
        float m_radius;
        float m_outlineWidth{};
        sf::Color m_fillColor;
        sf::Color m_outlineColor;
        float pointCount{};
    };
}

#endif //CIRCLE_HPP
