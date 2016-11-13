/*
Author: coderqiuan@163.com
Created on: 2016-11-11 10:38
 */

#pragma once

#include <string>
#include <assert.h>
#include <pthread.h>

#include "baseutil.h"

namespace qiuan
{
    namespace base
    {
        class CMutex
        {
            private:

                CMutex(const CMutex&);
                const CMutex& operator=(const CMutex&);

            public:

                explicit CMutex(const char* file = __FILE__, int line = __LINE__, const char* func = __func__)
                    : m_line(line),
                    m_file(file),
                    m_func(func)
            {
                if(0 != pthread_mutex_init(&m_mutex, NULL))
                {
                    printf("mutex %s failed,file:%s,line:%d,func:%s", __func__, m_file.c_str(), m_line, m_func.c_str());
                    assert(0);
                }
            }

                ~CMutex()
                {
                    if( 0 != pthread_mutex_destroy(&m_mutex))
                    {
                        printf("mutex %s failed,file:%s,line:%d,func:%s", __func__, m_file.c_str(), m_line, m_func.c_str());
                        assert(0);
                    }
                }

                void Lock()
                {
                    if(0 != pthread_mutex_lock(&m_mutex))
                    {
                        printf("mutex %s failed,file:%s,line:%d,func:%s", __func__, m_file.c_str(), m_line, m_func.c_str());
                        assert(0);
                    }
                }

                void Unlock()
                {
                    if(0 != pthread_mutex_unlock(&m_mutex))
                    {
                        printf("mutex %s failed,file:%s,line:%d,func:%s", __func__, m_file.c_str(), m_line, m_func.c_str());
                        assert(0);
                    }
                }

            private:

                int m_line;
                std::string m_file;
                std::string m_func;

                pthread_mutex_t m_mutex;
        };

        class CMutexGuard
        {
            private:

                CMutexGuard(const CMutexGuard&);
                const CMutexGuard& operator=(const CMutexGuard&);

            public:

                explicit CMutexGuard(CMutex& mutex)
                    : m_mutex(mutex)
                {
                    m_mutex.Lock();   
                }

                ~CMutexGuard()
                {
                    m_mutex.Unlock();    
                }

            private:

                CMutex& m_mutex;
        };
    }
}
