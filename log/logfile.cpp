/*
Author: coderqiuan@163.com
Created on: 2016-11-10 17:02
 */

#include "logfile.h"

using namespace qiuan::log;

static const std::string k_log_file_start = "============================== START ==============================";

CLogFile::CLogFile(const std::string base_name,
		size_t max_file_size,
		size_t flush_interval,
		size_t check_every_line)
	: m_basename(base_name)
	, m_maxfilesize(max_file_size)
	, m_flushinterval(flush_interval)
	, m_checkeveryline(check_every_line)
	, m_writefile(NULL)
{
    append(k_log_file_start.c_str(), k_log_file_start.size());
}

CLogFile::~CLogFile()
{
	if(NULL != m_writefile)
	{
		delete m_writefile;
	}
}

bool CLogFile::append(const char* in_buf, size_t in_len)
{
	CMutexGuard g(m_mutex);

	if(NULL == m_writefile)
	{
		m_writefile = new CWriteFile(get_log_file_name());
	}

    if(NULL == m_writefile)
    {
        return false;
    } else if(0 == m_writefile->write(in_buf, in_len)) {
        delete m_writefile;
        m_writefile = NULL;

        return false;
    } else {
        return true;
    }
}

std::string CLogFile::get_log_file_name()
{
	char log_name[128] = { 0 };

	return log_name;
}

