/*
Author: coderqiuan@163.com
Created on: 2016-11-23 11:28
*/

#include "base/baseuid.h"

using namespace qiuan::base;

int test_uid(int argc, char* argv[])
{
    s_uid_init(2, 3);

    uint64_t uid = s_uid_get(2, 3);

    printf("test_uid:%llu,%s\n", uid, s_uid_log(2, 3).c_str());
}

