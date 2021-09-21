#include <string>
#include <list>
#include "Miner.hpp"
#include "Observer.hpp"

using namespace std;

class BlockChain : public Observer
{
private:
    static BlockChain *instance; //singleton
    bool solved;                 //indica se il blocco è stato risolto per fermare il miner
    Miner miner;
    list<Blocco> blockChain;
    int port;
    BlockChain(int* port);

public:
    static BlockChain *getInstance(int* port);
    void AddBlock(Blocco *); //aggiunge il blocco alla lista
    Blocco *Mine();
    virtual void update(const string &blockchain) override; //innescato dal notify observer
    const string toJson();                                  // trasforma la lista in json
    friend class Node;
};