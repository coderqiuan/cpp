/*
Author: coderqiuan@163.com
Created on: 2016-11-10 18:15
*/

#include "test_file.cpp"
#include "test_time.cpp"

#include <pwd.h>

int main(int argc, char* argv[])
{
    test_time(argc, argv);

    test_file(argc, argv);



    struct passwd pwd;
    struct passwd* result = NULL;
    char buf[8192];

    getpwuid_r(::getuid(), &pwd, buf, sizeof buf, &result);
    if (result)
    {
        printf("name:%s\n", pwd.pw_name);
        printf("pwd:%s\n", pwd.pw_passwd);
    }

    if (::gethostname(buf, sizeof buf) == 0)
    {
        buf[sizeof(buf)-1] = '\0';
        printf("gethostname:%s\n", buf);
    }

    char path[128] = { 0 };
    sprintf(path, "/proc/%d/exe", ::getpid());
    CReadFile readfile(path);
    std::string procname;
    if(CReadFile::READ_COMPLETE == readfile.read(procname))
    {
        printf("procname:%s\n", procname.c_str());
    } else {
        printf("read procname failed:%d", readfile.get_errno());
    }

    return 0;
}

