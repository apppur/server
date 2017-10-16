#ifndef _ENGINE_TIMER_H_
#define _ENGINE_TIMER_H_

class engine_timer {
    public:
        engine_timer();
        ~engine_timer();

        void timer_init();
        void timer_update();
        void timer_timeout();
        void timer_start();

    private:
};
#endif
