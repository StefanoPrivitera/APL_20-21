#include "Gossiper.hpp"
Gossiper *Gossiper::instance = 0;
Gossiper::Gossiper(int* valuePort, int* serverPort) //Costruttore Gossiper valuePort porta del client, serverPort porta del nodo a cui si collega il client
{
  Observer::scelta = 2;
  this->nodes.insert(*valuePort);
  this->nodes.insert(*serverPort);
  std::thread th2([this]
                  { this->Gossip(); }); //creo un thread che gestisce la lista dei nodi attivi
  th2.detach();
}

Gossiper::~Gossiper() {}

Gossiper *Gossiper::getInstance(int* valuePort, int* serverPort) //pattern singleton 
{
  if (instance == 0)
  {
    instance = new Gossiper(valuePort, serverPort);
  }
  return instance;
}




int Gossiper::Gossip() //funzione che invia la lista dei nodi attivi a tutti ogni 5 secondi 
{
  while (true)
  {
    std::set<int>::iterator it;
    for (it = this->nodes.begin(); it != this->nodes.end(); ++it) //connetto il client a tutti i nodi che operano sulla blockchain (Il client ha la lista di tutti i nodi)
    {
      int portServer = *it;
      int sock = 0, valread;
      struct sockaddr_in serv_addr;

      if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
      {
        printf("\n Socket creation error \n");
        
        continue;
      }

      serv_addr.sin_family = AF_INET;
      serv_addr.sin_port = htons(portServer);

      // Convert IPv4 and IPv6 addresses from text to binary form
      if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
      {
        printf("\nInvalid address/ Address not supported \n");
        
        continue;
      }

      if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
      {
        continue;
      }
      send(sock, "2", 1, 0);    // invio il numero 2 in modo che il server capisce che sto inviando la lista dei nodi 
      string json = this->toJson(); // trasforma la lista dei nodi in json 
      char data[json.length() + 1];
      strcpy(data, json.c_str());
      send(sock, data, json.length() + 1, 0);
    }
    sleep(5);
  }
}

void Gossiper::Client(const string &blockChain)  // Invio tutta la blockchain (vuol dire che ho risolto un blocco)
{
  std::set<int>::iterator it;
  for (it = this->nodes.begin(); it != this->nodes.end(); ++it)
  {
    this->blockChain = blockChain;
    int portServer = *it;
    int sock = 0, valread;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      printf("\n Socket creation error \n");
      continue;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portServer);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
      printf("\nInvalid address/ Address not supported \n");
      continue;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
      printf("\nConnection Failed \n");
      continue;
    }
    send(sock, "1", 1, 0);
    string json = this->blockChain;
    // inizio prova
    long long int x = static_cast<int>(json.length()); // invio prima la lunghezza della blockchain
    std::string s2 = std::to_string(x);
    s2 = std::string(1024 - s2.length(), '0') + s2;
    char const *pchar2 = s2.c_str();
    send(sock, pchar2, 1024, 0);
    //fine prova
    
    char data[json.length() + 1];
    strcpy(data, json.c_str());
    send(sock, data, json.length() + 1, 0);// invio l'intera blockchain
    continue;
  }
}
void Gossiper::update(const string &setNodes) //triggerato da notifyobserver aggiorno la lista di nodi
{
  json jReceive;
  jReceive = json::parse(setNodes);

  for (json::iterator it = jReceive.begin(); it != jReceive.end(); ++it)
  {
    int number = it.value()["port"];
    
    nodes.insert(number);
  }
}
string Gossiper::toJson()
{

  json jSend;
  std::set<int>::iterator it;
  int i = 0;
  for (it = nodes.begin(); it != nodes.end(); ++it)
  {

    jSend[to_string(*it)] = {
        {"port", *it},
    };
  }

  string dumpIt = jSend.dump();

  return dumpIt;
}
