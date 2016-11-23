/*
Author: coderqiuan@163.com
Created on: 2016-11-22 17:39
*/

#pragma once

#include <map>
#include <string>
#include <inttypes.h>

#include "baseutil.h"
#include "singleton.h"

/*
   0---0000000000 0000000000 0000000000 0000000000 0 --- 00000 ---00000 ---0000000000 00
   第一位未使用
   41位为毫秒级时间(2039/9/7 23:47:35)
   5位模块标识位(32)，
   5位机器ID(32)
   12位该毫秒内的计数
   加起来刚好64位，为一个Long型。
   这样的好处是，整体上按照时间自增排序，并且整个分布式系统内不会产生ID碰撞
 */

namespace qiuan
{
    namespace base
    {
        class CUid
        {
            public:
            //protected:

                CUid(uint8_t module_id, uint8_t machine_id);

                friend class CUidManager;

            public:

                ~CUid();

                uint64_t uid();

                std::string log();

            private:

                uint16_t m_seqno;
                uint16_t m_moduleid;
                uint16_t m_machineid;
                uint64_t m_laststamp;
        };

        class CUidManager
        {
            private:

                CUidManager();

                friend class CSingleton<CUidManager>;

            public:

                ~CUidManager();

                int init(uint8_t module_id, uint8_t machine_id);

                uint64_t uid(uint8_t module_id, uint8_t machine_id);

                std::string log(uint8_t module_id, uint8_t machine_id);

            private:

                typedef std::map<uint16_t, CUid> id_uid_map;

                id_uid_map m_uidmap;
        };
#define s_uid_get(module_id, machine_id) CSingleton<CUidManager>::Instance().uid(module_id, machine_id)

#define s_uid_log(module_id, machine_id) CSingleton<CUidManager>::Instance().log(module_id, machine_id)

#define s_uid_init(module_id, machine_id) CSingleton<CUidManager>::Instance().init(module_id, machine_id)


    }
}

