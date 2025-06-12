#pragma once
#include <SFML/Window.hpp>
#include <ActiveKeyBinding.hpp>
#include <Mouse.hpp>
#include <textbox.hpp>
#include <EventBinding.hpp>
#include <inputbox.hpp>
namespace sfui {
    /**
     * @brief 标题类型，使用宽字符串
     */
    using Title = std::wstring;

    /**
     * @brief 将std::string转换为Title（std::wstring）
     * @param str 输入的字符串
     * @return 转换后的宽字符串
     */
    Title TitleName(const std::string &str);

    using viewSize = sf::Vector2f; ///< 视图大小类型
    class Window; ///< 前置声明窗口类

    /**
     * @brief 界面抽象基类，定义界面生命周期、事件绑定、渲染等接口
     */
    class Page {
    public:
        Page(sf::RenderWindow *p_sfml_RenderWindow):m_mouse(p_sfml_RenderWindow){}
        /**
         * @brief 虚析构函数
         */
        virtual ~Page() = default;

        /**
         * @brief 更新界面一帧（更新视图并渲染）
         */
        void updateFrame();

        /**
         * @brief 绑定界面与所属窗口
         * @param p_window 窗口指针
         */
        void setWindow(Window *p_window);

        /**
         * @brief 为界面鼠标绑定窗口
         * @param p_sfml_RenderWindow SFML窗口指针
         */
        void setMouseWindow(sf::RenderWindow *p_sfml_RenderWindow);

        /**
         * @brief 初始化界面（元素和消息绑定）
         */
        void init();

        /**
         * @brief 初始化界面元素（纯虚函数，需子类实现）
         */
        virtual void initializePageElements() = 0;

        /**
         * @brief 初始化消息与事件绑定（纯虚函数，需子类实现）
         */
        virtual void initMessageBinding() = 0;

        /**
         * @brief 绑定按键与行为（实时输入）
         * @param key 按键
         * @param action 行为
         */
        void activeMap(Key key, const Action &action);

        /**
         * @brief 绑定按键与行为（事件输入）
         * @param key 按键
         * @param action 行为
         */
        void eventMap(Key key, const Action &action);

        /**
         * @brief 绑定鼠标按键与行为（事件输入，重载）
         * @param mouseButton 鼠标按键（自定义类型）
         * @param action 行为
         */
        void eventMap(MouseButton mouseButton, const Action &action);

        /**
         * @brief 绑定SFML鼠标按键与区域及行为（事件输入，重载）
         * @param mouseButton SFML鼠标按键
         * @param area 触发区域指针
         * @param action 行为
         */
        void eventMap(sf::Mouse::Button mouseButton, const Area *area, const Action &action);

        /**
         * @brief 根据窗口大小更新界面视图（纯虚函数，需子类实现）
         */
        virtual void updateView() = 0;

        /**
         * @brief 实时输入处理（处理按键行为）
         */
        void executeKeyPressOnce();

        /**
         * @brief 事件输入处理（处理事件行为）
         * @param event SFML事件
         */
        void executeEventBinding(const sf::Event &event);

        /**
         * @brief 更新界面内容（纯虚函数，需子类实现）
         */
        virtual void update() = 0;

        /**
         * @brief 获取界面背景颜色
         * @return 背景颜色
         */
        [[nodiscard]] sf::Color getBackgroundColor() const;

    protected:
        Window *mp_window = nullptr; ///< 界面绑定的窗口
        sf::Color m_backgroundColor; ///< 界面背景颜色
        Mouse m_mouse; ///< 鼠标对象
        ActiveKeyBinding m_activeKeyBinding; ///< 按键事件绑定
        EvectBingding m_eventBinding; ///< 消息事件绑定

        /**
         * @brief 设置界面背景颜色
         * @param backgroundColor 新的背景颜色
         */
        void setBackgroundColor(const sf::Color &backgroundColor);

        /**
         * @brief 渲染界面内容（纯虚函数，需子类实现）
         */
        virtual void render() = 0;

        /**
         * @brief 发起界面跳转请求（由子类调用）
         * @param targetPageTitle 目标页面标题
         */
        void requestPageSwitch(const Title &targetPageTitle) const;
    };
}
