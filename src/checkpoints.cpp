// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Copyright (c) 2014 BlitzCoin Developers

// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
            boost::assign::map_list_of
            (     0, uint256("0xafaf057ef023cb6799f554c9faef896d20eda2594b8ee02c32f165486d4751ec"))
            (   100, uint256("0xa0d7b106ae20ef57386998369826bfd87ea1d1c8af53984820f4e7c85a1c6f1c"))
            (   150, uint256("0xbe14b2084e69121890fd2dea6a1e6644e7b0632471436adaac0fd9200bd43dbc"))
            (   303, uint256("0x879902ffd867f4843bbba2c25ce43e32cba896b856c620afc5391ea6a4a9da79"))
            (   500, uint256("0xeff58a380b74b9d5b0ecd1090fbc4732a7fac7ede4b078f23e1d7cf0aba6f84e"))
            (   700, uint256("0x53e0f3005e6429ab162fcf73b398dda0afe71eb5e5bb8a9dd0d9ab6a47b5b318"))
            (   999, uint256("0xedb846f5fd67278b47b160cf00a4f4a1d8a5ee83a4b01fccf43bbfc37a09ebfa"))
            (  1500, uint256("0xed3a473ad4b9cdc66f345af53d130e3b5f0cd824fb129b713158001d76d87c1d"))
            (  1901, uint256("0xeedee54336e3d372d2d17efa02fce71c10a49d0172daa781259b5b9d919fa380"))
            (  2203, uint256("0xfca331d8f613bdcb924570b8f993cfee409e1f78ec2f2afd8347b33efad2d33a"))
            ;


    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints

        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
