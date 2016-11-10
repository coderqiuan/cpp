/*
Author: coderqiuan@163.com
Created on: 2016-11-09 14:47
 */

#pragma once

#include <string>
#include <inttypes.h>

namespace qiuan
{
    namespace base
    {
        class CReadFile
        {
            private:

                CReadFile(const CReadFile&);
                const CReadFile& operator=(const CReadFile&);

                static const size_t k_read_buffer_size = 64 * 1024;

            public:

                CReadFile(std::string file_name);

                ~CReadFile();

                enum ReadType
                {
                    READ_CONTINUE = 0,
                    READ_COMPLETE,
                    READ_ERROR,
                };

                ReadType read(size_t size = k_read_buffer_size);

                ReadType read(std::string& out_buf, size_t max_file_size = k_read_buffer_size);

                int get_errno() { return m_errno; }

                int get_file_size() { return m_filesize; }

                int get_read_size() { return m_readsize; }

                int get_create_time() { return m_createtime; }

                int get_modify_time() { return m_modifytime; }

                //int get_cur_size() { return m_cursize; }

                const char* get_buffer() { return m_buffer; }

            private:

                int m_file;
                int m_errno;

                size_t m_filesize;
                size_t m_readsize;
                uint64_t m_createtime;
                uint64_t m_modifytime;

                ssize_t m_cursize;
                char m_buffer[k_read_buffer_size + 1 + 1];//+1 for read size=0
        };

        class CWriteFile
        {
            private:

                CWriteFile(const CWriteFile&);
                const CWriteFile& operator=(const CWriteFile&);
                static const size_t k_write_buffer_size = 64 * 1024;

            public:

                CWriteFile(std::string file_name);

                ~CWriteFile();

                size_t write(const std::string in_str);

                size_t write(const char* in_buf, size_t in_len);

                void flush();

                int get_errno() { return m_errno; }

            private:

                int m_errno;
                FILE* m_file;

                char m_buffer[k_write_buffer_size + 1];
        };
    }
}
