// -------------------------------------------------------------------
//
// perf_count.cc:  performance counters LevelDB (http://code.google.com/p/leveldb/)
//
// Copyright (c) 2012 Basho Technologies, Inc. All Rights Reserved.
//
// This file is provided to you under the Apache License,
// Version 2.0 (the "License"); you may not use this file
// except in compliance with the License.  You may obtain
// a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// software distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//
// -------------------------------------------------------------------

#ifndef STORAGE_LEVELDB_INCLUDE_PERF_COUNT_H_
#include "leveldb/perf_count.h"
#endif

#include "util/coding.h"
#include "util/crc32c.h"

namespace leveldb 
{

    SstCounters::SstCounters() 
        : m_IsReadOnly(false),
          m_Version(eSstCountVersion),
          m_CounterSize(eSstCountEnumSize)
    {
        memset(m_Counter, 0, sizeof(m_Counter));

        return;

    };  // SstCounters::SstCounters


    void 
    SstCounters::EncodeTo(
        std::string & Dst) const
    {
        unsigned loop;

        PutFixed32(&Dst, m_Version);
        PutFixed32(&Dst, m_CounterSize);
        
        for(loop=0; loop<eSstCountEnumSize; ++loop)
            PutFixed64(&Dst, m_Counter[loop]);
    }   // SstCounters::EncodeTo


    Status 
    SstCounters::DecodeFrom(
        const Slice& src)
    {
        Status ret_status;
        
        m_IsReadOnly=true;

        return(ret_status);

    }   // SstCounters::DecodeFrom


    uint64_t 
    SstCounters::Inc(
        unsigned Index) 
    {
        uint64_t ret_val;

        ret_val=0;
        if (!m_IsReadOnly && Index<m_CounterSize)
        {
            ++m_Counter[Index];
            ret_val=m_Counter[Index];
        }   // if 

        return(ret_val);
    }   // SstCounters::Inc


    uint64_t 
    SstCounters::Add(
        unsigned Index,
        uint64_t Amount)
    {
        uint64_t ret_val;

        ret_val=0;
        if (!m_IsReadOnly && Index<m_CounterSize)
        {
            m_Counter[Index]+=Amount;
            ret_val=m_Counter[Index];
        }   // if 

        return(ret_val);
    }   // SstCounters::Add

}  // namespace leveldb