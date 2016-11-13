/*
Author: coderqiuan@163.com
Created on: 2016-11-09 11:09
*/

#include "timestamp.h"

using namespace qiuan::base;

CTimeStamp::CTimeStamp(uint64_t usec)
{
    if(0 == usec)
    {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        m_usec = tv.tv_sec * k_microsercond_pre_second + tv.tv_usec;
    } else {
        m_usec = usec;
    }
}

CTimeStamp::CTimeStamp(const CTimeStamp& r)
{
    m_usec = r.m_usec;
}

const CTimeStamp& CTimeStamp::operator=(const CTimeStamp& r)
{
    if(&r != this)
    {
        m_usec = r.m_usec;
    }

    return *this;
}

CTimeStamp::~CTimeStamp()
{
    
}

uint64_t CTimeStamp::get_usec() const
{
    return m_usec;
}

uint64_t CTimeStamp::get_diff(const CTimeStamp timestamp) const
{
    if(timestamp.get_usec() > m_usec)
    {
        return timestamp.get_usec() - m_usec;
    } else {
        return m_usec - timestamp.get_usec();
    }
}


std::string CTimeStamp::to_string(TimeType type) const
{
    struct tm tm_time;
    time_t second = static_cast<time_t>(m_usec / k_microsercond_pre_second);

    //if(NULL == gmtime_r(&second, &tm_time))
    if(NULL == localtime_r(&second, &tm_time))
    {
        perror("CTimeStamp::to_string  error");

        return "timestamp_tostring_error";
    } else {
        char out_buf[32] = { 0 };

        if(TIME_LOG == type)
        {
            snprintf(out_buf, sizeof(out_buf), "%04d%02d%02dT%02d:%02d:%02d.%06d",
                    tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                    tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
                    static_cast<int>(m_usec % k_microsercond_pre_second));
        } else if(TIME_BASE == type) {
            snprintf(out_buf, sizeof(out_buf), "%04d-%02d-%02d %02d:%02d:%02d",
                    tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                    tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
        } else if(TIME_NAME == type) {
            snprintf(out_buf, sizeof(out_buf), "%04d%02d%02d%02d%02d%02d",
                    tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
                    tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
        } else {
            snprintf(out_buf, sizeof(out_buf), "undefined_timetype");
        }

        return out_buf;
    }
}

