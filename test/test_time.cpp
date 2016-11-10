/*
Author: coderqiuan@163.com
Created on: 2016-11-09 11:51
*/

#include "../base/timestamp.h"
#include "../base/baseheader.h"

using namespace qiuan::base;

int main(int argc, char* argv[])
{
    CTimeStamp timestamp;
    
    sleep_s(1);

    printf("time:%llu\n", timestamp.get_usec());
    printf("diff:%llu\n", timestamp.get_diff(CTimeStamp()));
    printf("log:%s\n", timestamp.to_string(CTimeStamp::TIME_LOG).c_str());
    printf("base:%s\n", timestamp.to_string(CTimeStamp::TIME_BASE).c_str());
    printf("name:%s\n", timestamp.to_string(CTimeStamp::TIME_NAME).c_str());

    return 0;
}
