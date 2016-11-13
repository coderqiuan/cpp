/*
Author: coderqiuan@163.com
Created on: 2016-11-10 14:21
 */

#pragma once

#include "base/fileutil.h"
#include "base/timestamp.h"
#include "base/mutexutil.h"

using namespace qiuan::base;

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
						size_t check_every_line = 1024);

				~CLogFile();

				bool append(const char* in_buf, size_t in_len);

			private:

				std::string get_log_file_name();

			private:

				std::string m_basename;
				size_t m_maxfilesize;
				size_t m_flushinterval;
				size_t m_checkeveryline;

                CMutex m_mutex;
				CWriteFile* m_writefile;
		};
	}
}

