

#include "Blocco.hpp"
#include "Observer.hpp"
class Miner:public Observer{

private:

public:
    Miner();
    Blocco *current;
    bool solved;
    string sha256(const string &);
    string calculateHash(const Blocco *);
    Blocco* run(const Blocco &);
    string setDifficulty(const Blocco &current, bool add);
    virtual void update(const string& file) override;
};