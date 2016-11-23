/*
Author: coderqiuan@163.com
Created on: 2016-11-09 11:05
 */

#pragma once

#include <string>
#include <sstream>

#include <unistd.h>

namespace qiuan
{
    namespace base
    {
        pid_t pid() { return ::getpid(); }

        inline void sleep_s(uint32_t sec) { sleep(sec); }
        inline void sleep_ms(uint32_t msec) { usleep(msec * 1000); }

        template<typename Type> Type to_number(std::string in_str)
        {
            Type value;
            std::stringstream ss;

            ss << in_str;
            ss >> value;

            return value;
        }

        template<typename Type> std::string to_string(Type value)
        {
            std::stringstream ss;

            ss << value;

            return ss.str();
        }

        inline int to_string(char* in_buf, int in_len, const char* fmt, ...)
        {
            va_list args;

            va_start(args, fmt);

            int v = to_string(in_buf, in_len, fmt, args);

            va_end(args);

            return v;
        }

        inline int to_string(char* in_buf, int in_len, const char* fmt, va_list& args)
        {
            return vsnprintf(in_buf, in_len, fmt, args);
        }

        inline int sys_trim(const char* &start, const char* in_buf, int in_len)
        {
            if(NULL == in_buf || in_len <= 0)
            {
                return -1;
            }

            start = in_buf;

            const char* end = in_buf + in_len;

            while(start < end)
            {
                if(0 == *start)
                {
                    return 0;
                } else if((unsigned char)*start > 0x20) {
                    break;
                } else {
                    ++start;
                }
            }

            while(start < end)
            {
                --end;

                if((unsigned char)*end > 0x20)
                {
                    ++end;

                    break;
                }
            }

            return end - start;
        }

    }
}









