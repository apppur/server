#include <iostream>
#include <string.h>
#include <time.h>
#include "config.h"
#include "lua.hpp"
#include "engine_queue.h"
#include "engine_message.h"


static int engine_time(lua_State *L) {
    time_t now;
    time(&now);
    std::string now_time = ctime(&now);
    lua_pushstring(L, now_time.c_str());
    return 1;
}

int main(int argc, char** argv)
{
    if (argc == 2)
    {
        if (strcmp(argv[1], "-version") == 0) 
        {
            std::cout << "server engine marjon run: " 
                << argv[0] << " version: "
                << " major:" << ENGINE_VERSION_MAJOR
                << " minor:" << ENGINE_VERSION_MINOR
                << std::endl;
            return 0;
        }
    }
    std::cout << "engine start..." << std::endl;

    engine_queue<engine_message> msg_queue;
    engine_message msg;
    msg.set_message(1, 1, 1000, 2000, nullptr, 0);
    msg_queue.push(msg);
    engine_message tmsg;
    msg_queue.pop(tmsg);
    tmsg.dump_message();

    lua_State *state = luaL_newstate();
    luaL_openlibs(state);
    luaL_dostring(state, "print(\"hello world!\")");
    lua_register(state, "engine_time", engine_time);
    luaL_dostring(state, "print(engine_time())");

    lua_close(state);

    return 0;
}