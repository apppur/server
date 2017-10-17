#ifndef _ENGINE_TIMER_H_
#define _ENGINE_TIMER_H_
#include <functional>
#include <vector>

typedef std::function<void(uint64_t)> timer_callback_t;

struct timer_event {
    unsigned int handle;
    int session;
    timer_callback_t callback;
    uint64_t expire;
    uint64_t duration;
};

class timer_node {
    public:
        timer_node()
        {
            event_list.clear();
        }
        ~timer_node()
        {
        }
        void timer_push(timer_event& event) 
        {
            event_list.push_back(event);
        }
        void event_call()
        {
            for (auto& ev : event_list)
            {
                ev.callback(ev.handle);
            }
        }
    private:
        std::vector<timer_event> event_list;
        //uint64_t expire;
        //int32_t repeate;
};

class timer_wheel {
    private:
};

class engine_timer {
    public:
        // wheel size
        static const uint8_t WHEEL_SIZE = 255;
        // ms
        static const int32_t PRECISION = 10;
    public:
        engine_timer();
        ~engine_timer();

        void timer_init();
        void timer_update();
        void timer_timeout();
        void timer_start();

        int64_t milliseconds();
    private:
};
#endif
