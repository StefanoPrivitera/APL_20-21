#include "Node.hpp"

Node::~Node()
{
}

Node::Node(int* portServer, int* portClient) 
{
  this->bc = BlockChain::getInstance(portServer); //signleton
  this->s = Server::getInstance(portServer); //singleton
  this->g = Gossiper::getInstance(portClient, portServer); //singleton
  s->registerObserver(bc); //registriamo il pattern Observer per la blockchain
  s->registerObserver(&bc->miner); //registriamo il pattern Observer per il miner
  s->registerObserver(g); //registriamo il pattern Observer per il gossiper
  if (this->bc->blockChain.empty()) //se la blockchain non ha alcun blocco
  {
    this->bc->AddBlock(new Blocco(0, "", "", 0, "000ffb66ffc86f38d952786c6d696c79c2dbc239dd4e91b46729d73a27fb57e9", 0)); //settiamo il blocco Genesis (blocco 0) da cui far partire la catena
  }
  while (true)
  {
    Blocco *b = this->bc->Mine(); // esco sia se il blocco l'ho minato io, sia se l'ha minato qualcun'altro  
    if (b->cHash != "") //controllo se il blocco è stato risolto da node corrente o da altri nodi
      {
      b->node=*portServer;
      this->bc->AddBlock(b); //aggiungiamo il blocco alla lista se l'ha risolto il nodo corrente 
      this->g->Client(this->bc->toJson()); // viene inviata agli altri nodi la blockchain aggiornata
    }
    delete b;
  }
}
