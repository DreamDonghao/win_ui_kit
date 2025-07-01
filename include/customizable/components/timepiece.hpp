//
// Created by donghao on 25-6-28.
//
#ifndef TIMEPIECE_HPP
#define TIMEPIECE_HPP

#include <chrono>

namespace sfui {

    class Timepiece {
    public:
        using clock = std::chrono::steady_clock;

        explicit Timepiece(const std::chrono::milliseconds interval)
            : m_interval(interval), m_last(clock::now()) {}

        explicit operator bool() {
            if (const auto now = clock::now(); now - m_last >= m_interval) {
                m_last = now;
                return true;
            }
            return false;
        }

    private:
        std::chrono::milliseconds m_interval;
        clock::time_point m_last;
    };

    /**
 * @class TimeIntervalMs
 * @brief 用于测量时间间隔（以毫秒为单位）的高精度计时器类。
 *
 * 使用 C++ 标准库的 std::chrono::steady_clock，确保时间测量不受系统时间变化影响。
 * 支持获取上一次记录点到当前的间隔，以及重置计时起点。
 */
    class TimeIntervalMs {
    public:
        /// 使用 steady_clock 作为时间源，保证单调递增
        using Clock = std::chrono::steady_clock;

        /// 表示时间点的类型
        using TimePoint = Clock::time_point;

        /// 表示毫秒时间间隔
        using Duration = std::chrono::milliseconds;

        /**
         * @brief 构造函数，初始化计时器起点为当前时间。
         */
        TimeIntervalMs() : m_last(Clock::now()) {}

        /**
         * @brief 获取当前时间与上一次记录点之间的时间间隔（以毫秒为单位）。
         * @return 时间间隔，单位为毫秒。
         */
        [[nodiscard]] long long elapsed() const;

        /**
         * @brief 获取时间间隔并重置计时起点为当前时间。
         * @return 与上一次计时点之间的毫秒时间间隔。
         */
        long long reset();

    private:
        TimePoint m_last; ///< 上一次记录的时间点
    };

    // 实现部分

    inline long long TimeIntervalMs::elapsed() const {
        return std::chrono::duration_cast<Duration>(Clock::now() - m_last).count();
    }

    inline long long TimeIntervalMs::reset() {
        const TimePoint now = Clock::now();
        const auto diff = std::chrono::duration_cast<Duration>(now - m_last);
        m_last = now;
        return diff.count();
    }

} // namespace sfui

#endif // TIMEPIECE_HPP
