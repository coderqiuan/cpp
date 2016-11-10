/*
Author: coderqiuan@163.com
Created on: 2016-11-09 15:11
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
//#include <sys/types.h>

#include "fileutil.h"

/*
   linux中文件描述符有一个属性:CLOEXEC,当调用exec成功后，文件会自动关闭。在2.6.23以前需要调用fcntl(fd,F_SETFD, FD_CLOEXEC),来设置这个属性。在新版本中只需要在open函数中设置O_CLOEXEC这个标志就可以。
   虽然新版本支持在open时设置CLOEXEC，但是在编译的时候还是会提示错误 - error: ‘O_CLOEXEC’ undeclared (first use in this function)。原来这个新功能要求我们手动去打开，需要设置一个宏(_GNU_SOURCE)。可通过以下两种方法来设置这个宏以打开新功能：
   1. 在源代码中加入 #define _GNU_SOURCE
   2. 在编译参数中加入 -D_GNU_SOURCE
 */
#define _GNU_SOURCE

using namespace qiuan::base;

CReadFile::CReadFile(std::string file_name)
    : m_file(::open(file_name.c_str(), O_RDONLY | O_CLOEXEC))
    , m_filesize(0)
    , m_readsize(0)
    , m_createtime(0)
    , m_modifytime(0)
{
    if(m_file < 0)
    {
        m_errno = errno;
    } else {
        m_errno = 0;
    }

    m_buffer[0] = '\0';
}

CReadFile::~CReadFile()
{
    if(m_file >= 0)
    {
        ::close(m_file);
    }
}

CReadFile::ReadType CReadFile::read(size_t size)
{
    m_buffer[0] = '\0';

    ssize_t read_size = 0;

    if(m_file >= 0)
    {
        struct stat statbuf;

        if(0 == m_filesize)
        {
            if(0 == ::fstat(m_file, &statbuf))
            {
                if(S_ISREG(statbuf.st_mode)) //是否为一般文件
                {
                    m_filesize = statbuf.st_size;
                    m_createtime = statbuf.st_ctime;
                    m_modifytime = statbuf.st_mtime;
                }
                else if (S_ISDIR(statbuf.st_mode)) //是否为目录
                {
                    m_errno = EISDIR;
                }
            } else {
                m_errno = errno;
            }
        }

        if(0 == m_errno)
        {
            size = size > k_read_buffer_size ? k_read_buffer_size : size;
            size = 0 == size ? 1 : size;
            read_size = ::read(m_file, m_buffer, size);

            if(read_size < 0)
            {
                m_errno = errno;
            } else {
                m_readsize += read_size;
                m_buffer[read_size] = '\0';
            }
        }
    }

    if(0 != m_errno)
    {
        return READ_ERROR;
    } else if(0 == read_size || (read_size > 0 && read_size < size)) {
        return  READ_COMPLETE;
    } else {
        return READ_CONTINUE;
    }
}

CReadFile::ReadType CReadFile::read(std::string& out_buf, size_t max_file_size)
{
    CReadFile::ReadType type = READ_COMPLETE;

    size_t last_out_buf_size = out_buf.size();
    max_file_size = 0 == max_file_size ? 1 : max_file_size;

    while(out_buf.size() - last_out_buf_size < max_file_size)
    {
        type = read(max_file_size);

        if(CReadFile::READ_CONTINUE == type) {
            out_buf += m_buffer;
        } else if(CReadFile::READ_COMPLETE == type) {
            out_buf += m_buffer;
            break;
        } else {
            break;
        }
    }

    return type;
}

//////////////////////////////////////////////////////////////////////

CWriteFile::CWriteFile(std::string file_name)
: m_file(::fopen(file_name.c_str(), "abe")) //'e' for O_CLOEXEC
{
    if(NULL == m_file)
    {
        m_errno = errno;
    } else {
        m_errno = 0;
        ::setbuffer(m_file, m_buffer, k_write_buffer_size);
    }
}

CWriteFile::~CWriteFile()
{
    if(NULL != m_file)
    {
        ::fclose(m_file);
    }
}

size_t CWriteFile::write(const std::string in_str)
{
    return write(in_str.c_str(), in_str.size());    
}

size_t CWriteFile::write(const char* in_buf, size_t in_len)
{
    size_t resend = 0;

    do
    {
        if(NULL == m_file || 0 != m_errno || 0 == in_len)
        {
            break;
        }

#ifdef _FWRITE_UNLOCKED_
        size_t size = ::fwrite_unlocked(in_buf + resend, 1, in_len - resend, m_file);
#else
        size_t size = ::fwrite(in_buf + resend, 1, in_len - resend, m_file);
#endif

        if(0 == size)
        {
            m_errno = ::ferror(m_file);
        } else {
            resend += size;
        }

    }while(in_len - resend > 0);

    if(in_len == resend)
    {
        return in_len;
    } else {
        return 0;
    }
}

void CWriteFile::flush()
{
    ::fflush(m_file);    
}

