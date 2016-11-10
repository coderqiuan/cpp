/*
Author: coderqiuan@163.com
Created on: 2016-11-09 10:49
 */

#pragma once

#include <string>
#include <inttypes.h>
#include <sys/time.h>

namespace qiuan
{
    namespace base
    {
        class CTimeStamp
        {
            static const int k_microsercond_pre_second = 1000 * 1000;

            public:

                explicit CTimeStamp(uint64_t usec = 0);

                CTimeStamp(const CTimeStamp& r);

                const CTimeStamp& operator=(const CTimeStamp& r);

                ~CTimeStamp();

                uint64_t get_usec() const;

                uint64_t get_diff(const CTimeStamp timestamp) const;

                enum TimeType
                {
                    TIME_LOG = 0,
                    TIME_BASE, 
                    TIME_NAME,
                };

                std::string to_string(TimeType type = TIME_LOG) const;

            private:

                uint64_t m_usec;
        };
    }
}

