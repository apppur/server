#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string.h>
#include <time.h>
#include "config.h"
#include "lua.hpp"
#include "engine_queue.h"
#include "engine_message.h"


static const int thread_num = 4;
std::vector<int> timer_callback_ids;

int thread_func(int id) {
    std::cout << "thread: " << id  << " begin run..." << std::endl;
    for ( ; ; ) {
        //engine_message msg;
        //q.pop(msg);
        //msg.dump_message();
        std::cout << "thread: " << id << " TICK!" << std::endl;
        std::chrono::milliseconds dura(1000 * (id + 1));
        std::this_thread::sleep_for(dura);
    }
    return 0;
}

static int engine_time(lua_State *L) {
    time_t now;
    time(&now);
    std::string now_time = ctime(&now);
    lua_pushstring(L, now_time.c_str());
    return 1;
}

static int _cb(lua_State *L) {
    lua_rawgetp(L, LUA_REGISTRYINDEX, (const void*)_cb);
    lua_call(L, 0, 0);

    return 0;
}

static int callback(lua_State *L) {
    luaL_checktype(L, 1, LUA_TFUNCTION);
    lua_rawsetp(L, LUA_REGISTRYINDEX, (const void*)_cb);
    return 0;
}

static int timer_callback_register(lua_State *L) {
    static auto callback_uuid = 0;
    callback_uuid++;
    luaL_checktype(L, 1, LUA_TFUNCTION);
    lua_getglobal(L, "_timer_callback_table");
    lua_insert(L, 1);
    lua_rawseti(L, 1, callback_uuid);
    timer_callback_ids.push_back(callback_uuid);
    return 0;
}

static int create_timer_callback_table(lua_State *L) {
    lua_newtable(L);
    lua_setglobal(L, "_timer_callback_table");
    return 0;
}

static int timer_callback(lua_State *L) {
    lua_getglobal(L, "_timer_callback_table");
    for (auto id : timer_callback_ids) {
        lua_pushinteger(L, id);
        lua_gettable(L, 1);
        lua_call(L, 0, 0);
    }
    lua_pop(L, 1);
    return 0;
}

int main(int argc, char** argv)
{
    if (argc == 2)
    {
        if (strcmp(argv[1], "-version") == 0) 
        {
            std::cout << "server engine version: " 
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
    create_timer_callback_table(state);
    luaL_dostring(state, "print(\"hello world!\")");
    lua_register(state, "engine_time", engine_time);
    luaL_dostring(state, "print(engine_time())");
    lua_register(state, "engine_register", callback);
    lua_register(state, "engine_timer", timer_callback_register);
    lua_register(state, "engine_timer_callback", timer_callback);
    /* test callback */
    int result = luaL_loadfile(state, "./script/hello.lua");
    if (result == 0) {
        lua_pcall(state, 0, 0, 0);
        _cb(state);
    }

    unsigned int ncore = std::thread::hardware_concurrency();
    std::cout << ncore << " concurrent threads are supported." << std::endl;
    std::thread thread_pool[thread_num];
    for (auto i = 0; i < thread_num; i++) {
        thread_pool[i] = std::thread(thread_func, i);
    }

    std::cout << "launched threads from main thread." << std::endl;
    for (auto i = 0; i < thread_num; i++) {
        thread_pool[i].join();
    }

    lua_close(state);

    return 0;
}
