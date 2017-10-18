#include <chrono>
#include "engine_timer.h"

engine_timer::engine_timer() 
{
}

engine_timer::~engine_timer()
{
}

int64_t engine_timer::milliseconds()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

void engine_timer::timer_init()
{
}
void engine_timer::timer_update()
{
}
void engine_timer::timer_timeout()
{
}
void engine_timer::timer_start()
{
}
