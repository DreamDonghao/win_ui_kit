//
// Created by donghao on 25-8-12.
//
#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include <SFML/Graphics.hpp>

namespace sfui {
    class Rectangle {
    public:
        Rectangle (const float x, const float y, const float width, const float height, const sf::Color fillColor, const sf::Color outlineColor)
            :m_width(width),m_height(height),m_x(x),m_y(y),m_fillColor(fillColor),m_outlineColor(outlineColor){}

        void setPosition(const float x, const float y) {
            m_x = x;
            m_y = y;
        }

        void setSize(const float width, const float height) {
            m_width = width;
            m_height = height;
        }


        void draw(sf::RenderWindow &window)const {
            sf::RectangleShape rect({m_width,m_height});
            rect.setPosition(m_x-m_width/2,m_y-m_height/2);
            rect.setFillColor(m_fillColor);
            rect.setOutlineColor(m_outlineColor);
            rect.setOutlineThickness(3);
            window.draw(rect);

        }
    private:
        float m_width;
        float m_height;
        float m_x;
        float m_y;
        sf::Color m_fillColor{};
        sf::Color m_outlineColor{};
    };
} // sfui

#endif //RECTANGLE_HPP
