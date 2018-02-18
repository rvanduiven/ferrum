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

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
     // It'll only connect to one or two seed nodes because once it connects,
     // it'll get a pile of addresses with newer timestamps.
     // Seed nodes are given a random 'last seen time' of between one and two
     // weeks ago.
     const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int k = 0; k < count; ++k)
    {
        struct in_addr ip;
        unsigned int i = data[k], t;

        // -- convert to big endian
        t =   (i & 0x000000ff) << 24u
            | (i & 0x0000ff00) << 8u
            | (i & 0x00ff0000) >> 8u
            | (i & 0xff000000) >> 24u;

        memcpy(&ip, &t, sizeof(ip));

        CAddress addr(CService(ip, port));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

#define SHOW_LOG true

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xbf;
        pchMessageStart[1] = 0x0c;
        pchMessageStart[2] = 0x5b;
        pchMessageStart[3] = 0xdb;
        vAlertPubKey = ParseHex("45898397288b1e4264789957oyd4ldc63ae4a1a2523b24300a3de1c5c8f4ec1e13eece09ebb0e9514f7b2b7e65f35f3a6ef6279d512f755078347bdcdf4ac378704");
        nDefaultPort = 49046;
        nRPCPort = 49047;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);

            const char* pszTimestamp = "UK Banks: Price Returns in 2018";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1518973200, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1518973200;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 15785;

        hashGenesisBlock = genesis.GetHash();
#ifdef SHOW_LOG
        LogPrintf("genesis.hashGenesisBlock == %s\n", hashGenesisBlock.ToString().c_str());
        LogPrintf("genesis.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
        LogPrintf("genesis.nBits == %d\n", genesis.nBits);
        LogPrintf("genesis.nNonce == %d\n", genesis.nNonce);
#endif
        assert(hashGenesisBlock == uint256("0x11e8a83ba249db08d4f22ce703bdb29f9469226f4c6ef008287fe048a4b80542"));
        assert(genesis.hashMerkleRoot == uint256("0xf4c86a1e17a35a932f10d8da2a71e7e0c96d9afb0f93ae25284487cbcea0b2e2"));

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,35);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,18);
        base58Prefixes[SECRET_KEY] =     std::vector<unsigned char>(1,25);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,78);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4).convert_to_container<std::vector<unsigned char> >();

        vSeeds.push_back(CDNSSeedData("1","185.188.183.240"));   
        vSeeds.push_back(CDNSSeedData("2","188.36.188.175"));     
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        nPoolMaxTransactions = 3;

        strDarksendPoolDummyAddress = "";
        nLastPOWBlock = 350000;
        nPOSStartBlock = 4321;
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
        pchMessageStart[0] = 0xd4;
        pchMessageStart[1] = 0xc1;
        pchMessageStart[2] = 0xb2;
        pchMessageStart[3] = 0xdf;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("096c0f17b03507d43fa947e5aa7845e5d4398238bdccc0f658d67029224ad170babc8492d73bbc95ffca8f73eab12d9bb2d87ea6671b0ec023e2fdf1a141ac4624");
        nDefaultPort = 48812;
        nRPCPort = 48813;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 8);
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nTime    = 1518970100;
        genesis.nNonce = 44;
#ifdef SHOW_LOG
        LogPrintf("CTestNetParams.hashGenesisBlock == %s\n", hashGenesisBlock.ToString().c_str());
        LogPrintf("CTestNetParams.hashMerkleRoot == %s\n", genesis.hashMerkleRoot.ToString().c_str());
        LogPrintf("CTestNetParams.nBits == %d\n", genesis.nBits);
        LogPrintf("CTestNetParams.nNonce == %d\n", genesis.nNonce);
#endif
        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = std::vector<unsigned char>(1,15);
        base58Prefixes[SCRIPT_ADDRESS] = std::vector<unsigned char>(1,18);
        base58Prefixes[SECRET_KEY]     = std::vector<unsigned char>(1,25);
        base58Prefixes[STEALTH_ADDRESS] = std::vector<unsigned char>(1,80);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94).convert_to_container<std::vector<unsigned char> >();

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


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
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {

    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
