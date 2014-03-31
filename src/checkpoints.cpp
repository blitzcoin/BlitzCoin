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
            (  2701, uint256("0x85618f98239b0f120914c17f7f37795aa32887e9b17e026f0c00323e05a77b06"))
            (  3000, uint256("0xef6c66058e32c8d0d23161ef301988c04e9298157311b64c6fea1fe45e9b4bed"))
            (  3150, uint256("0x22cedee94491c18bbdcb0a4da50cdcb0692c46c3bfccfe8a9d7b543e43c2337d"))
            (  3375, uint256("0x89bc95c8f702110c9352ec8052a44e2cb318a26fef8c355036fe8f954043063e"))
            (  3501, uint256("0xc7acf01513dc369f7084bb8100bf198738f71750cb307d008ffd782c20cfc268"))
            (  4000, uint256("0xf3fe4dd7e942d62fcdc6527cac59501d93ec171cdb03edbfa3fc2e8c800d98a5"))
            (  4499, uint256("0x0c5039ee54a6f4a9a759fd76287e8e0c75bfa1d8f7dd120912be80bb6349b442"))
            (  5100, uint256("0xca403929392ed07614d01bb39616283daf2cfea848c156e939728d4654e86792"))
            (  5749, uint256("0x6537da1bc102baea63d91b6762496a4b89f1f0e4825572413252aa7e3cdf5c82"))
            (  6500, uint256("0x51962d710bfee2f1408a59bb464309a1bc7644fe2618ce8b961890849ff271c8"))
            (  7000, uint256("0x61109d85396e744a524ecff7f042b8eb5f6437fc27bfd215a97d1ee4849ab88f"))
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
