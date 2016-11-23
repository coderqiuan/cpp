/*
Author: coderqiuan@163.com
Created on: 2016-11-22 18:10
 */

#include <sys/time.h>

#include "baseuid.h"

static uint64_t get_cur_stamp()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (uint64_t)tv.tv_sec * 1000 + (uint64_t)tv.tv_usec / 1000;
}

using namespace qiuan::base;

CUid::CUid(uint8_t module_id, uint8_t machine_id)
    : m_seqno(0),
    m_moduleid(module_id),
    m_machineid(machine_id),
    m_laststamp(0)
{

}

CUid::~CUid()
{

}

uint64_t CUid::uid()
{
    uint64_t cur_stamp = get_cur_stamp();

    if(m_laststamp == cur_stamp) 
    {
        m_seqno = (m_seqno + 1) & 0xFFF;

        if(m_seqno == 0)
        {
            cur_stamp = get_cur_stamp();

            while(cur_stamp <= m_laststamp)
            {
                cur_stamp = get_cur_stamp();
            }
        }
    }
    else
    {
        m_seqno = 0;
    }

    m_laststamp = cur_stamp;

    return (m_laststamp & 0x1FFFFFFFFFF) << 22 | (m_moduleid & 0x1F) << 17 | (m_machineid & 0x1F) << 12 | (m_seqno & 0xFFF);
}

std::string CUid::log()
{
    char out_buf[1024] = { 0 };

    if(to_string(out_buf, 1024, "stamp:%llu,module_id:%u,machine_id:%u,m_seqno:%u", m_laststamp, m_moduleid, m_machineid, m_seqno) > 0)
    {
        return out_buf;
    } else {
        return "";
    }
}

CUidManager::CUidManager()
{

}

CUidManager::~CUidManager()
{

}

int CUidManager::init(uint8_t module_id, uint8_t machine_id)
{
    uint16_t key = (module_id << 8) | machine_id;    

    if(m_uidmap.end() == m_uidmap.find(key))
    {
        CUid uid(module_id, machine_id);

        m_uidmap.insert(std::make_pair(key, uid));

        return 1;
    } else {
        return -1;
    }
}

uint64_t CUidManager::uid(uint8_t module_id, uint8_t machine_id)
{
    uint16_t key = (module_id << 8) | machine_id;    

    id_uid_map::iterator it = m_uidmap.find(key);

    if(m_uidmap.end() == it)
    {
        return 0LL;
    } else {
        it->second.uid();
    }
}

std::string CUidManager::log(uint8_t module_id, uint8_t machine_id)
{
    uint16_t key = (module_id << 8) | machine_id;    

    id_uid_map::iterator it = m_uidmap.find(key);

    if(m_uidmap.end() == it)
    {
        return "";
    } else {
        it->second.log();
    }       
}



