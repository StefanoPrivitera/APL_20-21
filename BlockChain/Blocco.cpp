
#include <iostream>
#include <string>
#include "Blocco.hpp"
#include "json.hpp"
using json = nlohmann::json;
using namespace std;
Blocco::Blocco(int id, string cHash, string pHash, int nonce, string difficulty, long int timestamp)
{
    this->id = id;                 //id del blocco
    this->cHash = cHash;           //hash del blocco corrente
    this->pHash = pHash;           //hash del blocco precedente
    this->nonce = nonce;           //nonce (al fine di risolvere il blocco provo diversi nonce)
    this->difficulty = difficulty; //difficoltà utile per mantenere il tempo medio di un blocco a 15 secondi
    this->timestamp = timestamp;   //timestamp
}
Blocco::Blocco(int id, string cHash, string pHash, int nonce, string difficulty, long int timestamp, int node)
{
    this->id = id;
    this->cHash = cHash;
    this->pHash = pHash;
    this->nonce = nonce;
    this->difficulty = difficulty;
    this->timestamp = timestamp;
    this->node = node; //nodo che risolve il blocco
}
Blocco::Blocco(int id, string cHash, string pHash, int nonce, string difficulty, long int timestamp, int node, string file)
{
    this->id = id;
    this->cHash = cHash;
    this->pHash = pHash;
    this->nonce = nonce;
    this->difficulty = difficulty;
    this->timestamp = timestamp;
    this->node = node;
    this->files = file;
}

Blocco::Blocco()
{
    Blocco(0, "", "", 0, "", 0);
}

string Blocco::toString() const
{
    return to_string(id) + this->pHash + to_string(this->nonce);
}
string Blocco::toJson() const //trasformo l'oggetto blocco in json
{

    json jSend;
    jSend[this->id] = {
        {"id", this->id},
        {"cHash", this->cHash},
        {"pHash", this->pHash},
        {"nonce", this->nonce},
        {"difficulty", this->pHash},
        {"timestamp", this->timestamp},
        {"node", this->node},

    };

    string dumpIt = jSend.dump();
    return dumpIt;
}
