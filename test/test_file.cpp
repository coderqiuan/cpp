/*
Author: coderqiuan@163.com
Created on: 2016-11-09 17:02
 */

#include "../base/fileutil.h"
#include "../base/baseheader.h"

using namespace qiuan::base;

int main(int argc, char* argv[])
{
    std::string write_buffer = "1234567890";
    CWriteFile writefile("file.log");
    writefile.write(write_buffer);
    writefile.flush();

    size_t read_size = 3;

    if(argc > 1)
    {
        read_size = atoi(argv[1]);
    }
    printf("read_size:%lu\n", read_size);

    //>>1 begin
    std::string file_buffer;
    CReadFile readfile("file.log");         
    while(1)
    {
        CReadFile::ReadType type = readfile.read(read_size);

        file_buffer += readfile.get_buffer();

        printf("buffer:[%s]\n", file_buffer.c_str());

        if(CReadFile::READ_CONTINUE == type) {
            continue;
        }
        
        break;
    }

    if(0 == readfile.get_errno() && readfile.get_read_size() == readfile.get_file_size())
    {
        printf("buffer:[%s]\n", file_buffer.c_str());
    } else {
        printf("errno:%d,readsize:%d,filesize:%d\n", readfile.get_errno(), readfile.get_read_size(), readfile.get_file_size());
    }

    //<<1 end

    std::string file_buffer_2;
    CReadFile readfile2("file.log");
    while(CReadFile::READ_CONTINUE == readfile2.read(file_buffer_2, read_size))
    {
        printf("buffer2:[%s]\n", file_buffer_2.c_str());
    }

    if(0 == readfile2.get_errno() && readfile2.get_read_size() == readfile2.get_file_size())
    {
        printf("buffer2:[%s]\n", file_buffer_2.c_str());
    } else {
        printf("errno:%d,readsize:%d,filesize:%d\n", readfile2.get_errno(), readfile2.get_read_size(), readfile2.get_file_size());
    }
}

