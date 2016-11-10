/*
Author: coderqiuan@163.com
Created on: 2016-11-09 10:50
 */

#pragma once

namespace qiuan
{
    namespace base
    {
        template<typename T> class CSingleton
        {
            public:

                CSingleton()
                {

                }

                static T& Instance()
                {
                    static T instance;

                    return instance;
                }
        };
    }
}

