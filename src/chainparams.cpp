// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

unsigned int pnSeed[] =
{
0x7b0272a7, 0xada272a7
};

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xa2;
        pchMessageStart[1] = 0x7a;
        pchMessageStart[2] = 0xc1;
        pchMessageStart[3] = 0x7c;
        vAlertPubKey = ParseHex("046d4a82462704df06381163858c5998e85277d995967632348ecaa24668d48b7910bae9c427f6ae929907fc5a33b5d731dfb0e53a057a8200bc11eab87d693ef7");
        nDefaultPort = 20302;
        nRPCPort = 20304;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20);


        const char* pszTimestamp = "2015 DraftCoin Start!";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
		CTransaction txNew(1, 1432374838, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1432374838;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 330954;

        hashGenesisBlock = genesis.GetHash();
/*
        while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
            if (++genesis.nNonce==0) break;
            hashGenesisBlock = genesis.GetHash();
        }

        printf("%s\n MAIN ", hashGenesisBlock.ToString().c_str());
        printf("%s\n MAIN ", genesis.hashMerkleRoot.ToString().c_str());
        printf("%x\n MAIN ", bnProofOfWorkLimit.GetCompact());
        printf("%d\n MAIN ", genesis.nNonce);
*/
        assert(hashGenesisBlock == uint256("0x00000626d583465e39cc5eec2020f639792843efcfb4182d508e6734d4cfdab6"));
        assert(genesis.hashMerkleRoot == uint256("0x96b2046ee922b5724d19ade2ca7f44bc828e8b850f6e5416a98cf4fbea18ba87"));

		vSeeds.push_back(CDNSSeedData("dns.btcdraft.ca", "dns.btcdraft.ca"));
		vSeeds.push_back(CDNSSeedData("149.56.101.219", "149.56.101.219"));
		vSeeds.push_back(CDNSSeedData("158.69.199.130", "158.69.199.130"));
		vSeeds.push_back(CDNSSeedData("99.248.230.242", "99.248.230.242"));
	    	vSeeds.push_back(CDNSSeedData("68.206.29.192", "68.206.29.192"));
	    	vSeeds.push_back(CDNSSeedData("209.195.104.6", "209.195.104.6"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(30);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(91);
        base58Prefixes[SECRET_KEY] =     list_of(117);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x73)(0x77)(0xEE);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x73)(0xDD)(0x55);

        convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));

        nLastPOWBlock = 15000;

		// Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xaa;
        pchMessageStart[1] = 0x33;
        pchMessageStart[2] = 0xff;
        pchMessageStart[3] = 0x77;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0433ec1132f34b5d4cafe6e9b3d848b710d75d8ec7a363d24554eac5256e70e5850b33a716492f2570f6f0cc5b2d3c01c2dfb25bf0a9327e634dee8a3b2d1039bb");
        nDefaultPort = 12345;
        nRPCPort = 12346;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 81778;
        hashGenesisBlock = genesis.GetHash();
/*
        while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
            if (++genesis.nNonce==0) break;
            hashGenesisBlock = genesis.GetHash();
        }

        printf("%s\n TESTNET ", hashGenesisBlock.ToString().c_str());
        printf("%s\n TESTNET ", genesis.hashMerkleRoot.ToString().c_str());
        printf("%x\n TESTNET ", bnProofOfWorkLimit.GetCompact());
        printf("%d\n TESTNET ", genesis.nNonce);
*/
        assert(hashGenesisBlock == uint256("0x00007fe66ae67c7d800791c56234ef019ca1f85f9b059fcccc49447d33c22481"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(110);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196);
        base58Prefixes[SECRET_KEY]     = list_of(239);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x17)(0xFF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x43)(0x99);

        convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xaf;
        pchMessageStart[1] = 0xbb;
        pchMessageStart[2] = 0x55;
        pchMessageStart[3] = 0xdd;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1412222222;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 8;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 47992;
        strDataDir = "regtest";
/*
        while (hashGenesisBlock > bnProofOfWorkLimit.getuint256()){
            if (++genesis.nNonce==0) break;
            hashGenesisBlock = genesis.GetHash();
        }

        printf("%s\n REGTEST ", hashGenesisBlock.ToString().c_str());
        printf("%s\n REGTEST ", genesis.hashMerkleRoot.ToString().c_str());
        printf("%x\n REGTEST ", bnProofOfWorkLimit.GetCompact());
        printf("%d\n REGTEST ", genesis.nNonce);
*/
        assert(hashGenesisBlock == uint256("0x21a8f72f07cec34eb88c6088f382eeb868c9813adfb9edffbe40a5e076c14cb8"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
