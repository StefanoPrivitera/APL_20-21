#include "Gossiper.hpp"
#include "Server.hpp"
#include "BlockChain.hpp"
#include <fstream>
class Node 
{

public:
    BlockChain *bc;
    Server *s;
    Gossiper *g;
  
    Node(int* portClient,int* portServer);
    ~Node();
};