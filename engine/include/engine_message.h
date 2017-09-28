#ifndef _ENGINE_MESSAGE_H_
#define _ENGINE_MESSAGE_H_

class engine_message {
    public:
        engine_message();
        engine_message(int id, int type, int src, int dst, int sz, char* buffer) :
            m_id(id), m_type(type), m_src(src), m_dst(dst), m_sz(sz), m_buffer(buffer)
    {}
        ~engine_message();
        
    public:
        void set_message(int id, int type, int src, int dst, char* buffer, int sz);
        void dump_message();
    private:
        int m_id = 0;
        int m_type = 0;
        int m_src = 0;
        int m_dst = 0;
        int m_sz = 0;
        char* m_buffer = nullptr;
};

#endif
