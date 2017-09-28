#include <iostream>
#include "engine_message.h"

engine_message::engine_message()
{
}

engine_message::~engine_message()
{
}

void engine_message::set_message(int id, int type, int src, int dst, char* buffer, int sz)
{
    m_id = id;
    m_type = type;
    m_src = src;
    m_dst = dst;
    m_buffer = buffer;
    m_sz = sz;
    return;
}

void engine_message::dump_message()
{
    std::cout << "msg id:" << m_id
        << " type:" << m_type
        << " src:" << m_src
        << " dst:" << m_dst
        << std::endl;
}
