//
// Created by donghao on 25-6-8.
//

#ifndef INPUTBOX_HPP
#define INPUTBOX_HPP
#include <textbox.hpp>
#include <area.hpp>
#include <iostream>
#include <print>

namespace sfui {
    class InputBox {
    public:
        InputBox(Mouse &mouse, const float x, const float y, const int width, const int height, const sf::Color color,
            const unsigned int textSize)
            : m_x(x), m_y(y), m_width(width), m_height(height), m_textbox(
                  m_x, m_y, textSize, color,
                  R"(C:\Users\donghao\AppData\Local\Programs\cursor\resources\app\out\media\jetbrains-mono-regular.ttf)",
                  "hello)"), m_inputArea(x, y, x + width, y + height), m_mouse(mouse) {
        }


        void run(const sf::Event &event) {
            if (m_mouse.isLeftPressed()) {
                if (m_inputArea.isInArea(m_mouse.getWindowPosition().x, m_mouse.getWindowPosition().y)) {
                    isActive = true;
                    std::println("isActive");
                } else {
                    isActive = false;
                }
            }
            if (isActive) {
                if (event.type == sf::Event::TextEntered) {
                    std::cout << event.text.unicode << std::endl;\
                    std::cout << cursorPosition << std::endl;
                    if (event.text.unicode == 8) {
                        if (cursorPosition >= 0) {
                            m_text.erase(m_text.begin() + cursorPosition);
                            cursorPosition--;
                        }
                    } else if (event.text.unicode < 128) {
                        m_text.insert(m_text.begin() + cursorPosition+1, static_cast<char>(event.text.unicode));
                        cursorPosition += 1;
                    }
                } else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Delete && cursorPosition < static_cast<int>(m_text.length())) {
                        m_text.erase(m_text.begin() + cursorPosition + 1);
                    } else if (event.key.code == sf::Keyboard::Left && cursorPosition >= 0) {
                        std::cout << "L" << cursorPosition << std::endl;
                        cursorPosition -= 1;
                    } else if (event.key.code == sf::Keyboard::Right && cursorPosition <  static_cast<int>(m_text.
                                   length())-1) {
                        std::cout << "R" << cursorPosition << std::endl;
                        cursorPosition += 1;
                    }
                }
                m_textbox.setTestString(m_text);
            }
        }

        const sfui::Area &getArea() const { return m_inputArea; }

        std::string &getText() { return m_text; }

        const sf::Text &getSpring() const {
            return m_textbox.getSprite();
        }

    private:
        float m_x;
        float m_y;
        int m_width;
        int m_height;
        bool isActive = false;
        std::string m_text;
        TextBox m_textbox;
        Area m_inputArea;
        int cursorPosition = -1;
        std::string cursorStyle = "|";
        Mouse &m_mouse;
    };
}


#endif //INPUTBOX_HPP
