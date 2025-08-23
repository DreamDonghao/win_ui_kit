//
// Created by donghao on 25-8-22.
//
#ifndef PROGRESSBAR_HPP
#define PROGRESSBAR_HPP
#include <SFML/Window.hpp>

#include "SFML/Graphics/RenderWindow.hpp"
#include <Rectangle.hpp>

namespace sfui {
    class ProgressBar {
    public:
        ProgressBar(const float x, const float y, const float width, const float height,
                    const double maxValue, const double currentValue)
            : m_x(x), m_y(y), m_width(width), m_height(height),
              m_maxValue(maxValue), m_currentValue(currentValue) {
        }

        virtual ~ProgressBar() = default;

        void updateCurrentValue(const double currentValue) {
            m_currentValue = currentValue;
        }

        [[nodiscard]] double getProgress() const {
              return m_currentValue / m_maxValue;
        }

        [[nodiscard]] double getCurrentValue() const {
            return m_currentValue;
        }

        void setMaxValue(const double maxValue) {
            m_maxValue = maxValue;
        }

        [[nodiscard]] double getMaxValue() const {
            return m_maxValue;
        }

        virtual void draw(sf::RenderWindow &window) {
            const Rectangle back(m_x, m_y, m_width, m_height, sf::Color::White, sf::Color::White);
            const double progress = getProgress();
            const Rectangle bar(
                m_x - m_width * (1 - progress) / 2, m_y,
                m_width * progress, m_height,
                sf::Color::Red, sf::Color::Red
            );
            back.draw(window);
            bar.draw(window);
        }

    private:
        float m_x;
        float m_y;
        float m_width;
        float m_height;
        double m_maxValue;
        double m_currentValue;
    };
} // sfui

#endif //PROGRESSBAR_HPP
