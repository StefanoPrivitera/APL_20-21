#include <iostream>
#include <string>
#include "BlockChain.hpp"
#include "Server.hpp"
#include "Gossiper.hpp"
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

BlockChain *BlockChain::instance = 0;

BlockChain::BlockChain(int* port)
{
    Observer::scelta = 1; //Strategy dentro observer
    this->port = *port;    //porta dove si collega il nodo
}

BlockChain *BlockChain::getInstance(int* port)
{
    if (instance == 0)
    {
        instance = new BlockChain(port); // singleton
    }
    return instance;
}

void BlockChain::AddBlock(Blocco *b)
{

    blockChain.push_back(*b); //aggiunge il blocco risolto alla lista
}
Blocco *BlockChain::Mine() // Chiama il miner per risolvere il blocco
{

    Blocco *b = this->miner.run(blockChain.back()); //passo l'ultimo blocco
    return b;
}
void BlockChain::update(const string &blockChain) //triggerato da notify observer
{
    json jReceive;
    jReceive = json::parse(blockChain);

    json::iterator it = jReceive.end();
    --it;
    int id = this->blockChain.back().id;

    int i = it.value()["id"];

    if (i > id) // se la blockchain che ricevo è piu lunga di quella corrente
    {
        this->blockChain.clear();                                              //cancella la blockchain
                                                                               //fermo il miner
        for (json::iterator it = jReceive.begin(); it != jReceive.end(); ++it) //construisco la nuova blockchain a partire da quella ricevuta
        {
            int number = it.value()["id"];
            Blocco *b = new Blocco(number, it.value()["cHash"], it.value()["pHash"], it.value()["nonce"], it.value()["difficulty"], it.value()["timestamp"], it.value()["node"], it.value()["file"]);
            this->miner.solved = true;
            this->AddBlock(b); //aggiungo il nuovo blocco alla lista di nodi
            delete b;
        }
    }
}
const string BlockChain::toJson() //Trasformo la lista dei nodi in json
{

    json jSend;
    std::list<Blocco>::iterator it;
    for (it = blockChain.begin(); it != blockChain.end(); ++it)
    {

        jSend[it->id] = {
            {"id", it->id},
            {"cHash", it->cHash},
            {"pHash", it->pHash},
            {"nonce", it->nonce},
            {"difficulty", it->pHash},
            {"timestamp", it->timestamp},
            {"node", it->node},
            {"file", it->files}};
    }
    string dumpIt = jSend.dump();
    return dumpIt;
}
