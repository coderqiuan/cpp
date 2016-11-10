/*
Author: coderqiuan@163.com
Created on: 2016-11-10 14:21
*/

#pragma once

namespace qiuan
{
namespace log
{
class CLogFile
{
private:
    CLogFile(const CLogFile&);
    const CLogFile& operator=(const CLogFile&);

    static const size_t k_log_file_size = 5 * 1024 * 1024;

    public:

    CLogFile(const std::string base_name,
        size_t max_file_size = k_log_file_size,
        size_t flush_interval = 3,
        size_t check_every_line = 1024,
        bool check_per_day = true);


};
}
}

