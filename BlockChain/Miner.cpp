#include <openssl/sha.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string.h>
#include "Miner.hpp"
#include "uint256_t/uint256_t.h"
#include <unistd.h>
using namespace std;
#include "json.hpp"
using json = nlohmann::json;
Miner::Miner()
{
    Observer::scelta = 4;
}

Blocco *Miner::run(const Blocco &b) //provo a risolvere il blocco
{
    current = new Blocco();
    current->pHash = b.cHash; //hash del blocco precedente
    current->id = b.id + 1;
    current->files.clear();
    current->difficulty = b.difficulty;
    current->nonce = rand();
    time_t start = time(0);
    solved = false;
    while (!solved)
    {
        sleep(0.1);                                                // per non distruggere il pc
        string hash = calculateHash(current);                      // calcolo l'hash del blocco
        if (strcmp(hash.c_str(), current->difficulty.c_str()) < 0) // verifico se appartiene alla famiglia di soluzioni
        {
            solved = true;
            current->cHash = hash;
            current->after = difftime(time(0), start);
            current->timestamp = time(0);
            if (current->after < 15) //se passa un tot di tempo < 5
            {
                current->difficulty = this->setDifficulty(*current, false); //passato troppo tempo, diminuiamo la difficoltà
            }
            if (current->after > 15)
            {
                current->difficulty = this->setDifficulty(*current, true); //passato poco tempo, aumentiamo la difficoltà
            }

            cout << "Id " << current->id << endl;
            cout << "Nonce " << current->nonce << endl;
            cout << "Hash " << current->cHash << endl;
            cout << "Previous " << current->pHash << endl;
            cout << "Timestamp " << current->timestamp << endl;
            cout << "Dopo " << current->after << endl;
            cout << "Difficoltà " << current->difficulty << endl;
            cout << "File" << current->files << endl;
            cout << endl;
        }
        current->nonce += 1;
    }

    return current;
}

string Miner::calculateHash(const Blocco *b) //calcolo hash del blocco
{

    string hash = sha256(b->toString());
    return hash;
}
string Miner::sha256(const string &str) //uso dell'algoritmo sha256
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }
    return ss.str();
}
string Miner::setDifficulty(const Blocco &current, bool add) //aggiustamento della difficoltà
{
    uint256_t val(current.difficulty);
    if (add)
        val *= 2; //aumentiamo la difficoltà
    else
        val /= 2; //diminuiamo la difficoltà
    std::stringstream sstream;
    sstream << std::hex << val;
    std::string result = sstream.str();
    if (result.length() < 64)
    {
        result = std::string(64 - result.length(), '0').append(result);
    }

    return result;
}
void Miner::update(const string &file) // triggerato da notify observer aggiunge una stringa custom al blocco( può contenere file codificati, dns o altro)
{
    this->current->files = file;
}
