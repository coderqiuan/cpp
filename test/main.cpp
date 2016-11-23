/*
Author: coderqiuan@163.com
Created on: 2016-11-10 18:15
*/

//#include "test_uid.cpp"
//#include "test_file.cpp"
//#include "test_time.cpp"

#include <pwd.h>


#include "base/baseuid.h"

using namespace qiuan::base;

int test_uid(int argc, char* argv[])
{
        //s_uid_init(2, 3);

//            uint64_t uid = s_uid_get(2, 3);

  //              printf("test_uid:%llu,%s\n", uid, s_uid_log(2, 3).c_str());
  CUid uid(0, 0);
}

int main(int argc, char* argv[])
{
    test_uid(argc, argv);

    //test_time(argc, argv);

    //test_file(argc, argv);

/*


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
*/
    return 0;
}

