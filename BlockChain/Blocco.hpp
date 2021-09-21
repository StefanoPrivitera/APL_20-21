#pragma once
#include <iostream>
#include <string>
#include "uint256_t/uint256_t.h"
#include <map>
using namespace std;

class Blocco
{
private:
    int id, nonce;
    string cHash;
    string pHash;
    string difficulty;
    long int timestamp;
    double after; // differenza tra timestamp
    int node;
    string files;
    string fileToJson();

public:
    Blocco(int id, string cHash, string pHash, int nonce, string difficulty, long int timestamp,int node=0,string file="");
    Blocco();
    string toString() const;
    string toJson() const;
    friend class Miner;
    friend class BlockChain;
    friend class Node;
};
