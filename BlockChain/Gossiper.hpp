#include <thread>
#include <map>
#include <iostream>
#include <cassert>

#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib> // For exit() and EXIT_FAILURE
#include <iostream> // For cout
#include <unistd.h> // For read
#include <thread>         // std::thread
#include <stdio.h>
#include <stdlib.h>
#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include "json.hpp"
#include "Blocco.hpp"
#include <set>
#include "Observer.hpp"
#define PORT 9997
using namespace std;
using json = nlohmann::json;
using namespace std;

class Gossiper:public Observer
{
private:

    int port;
    static Gossiper *instance;
    string blockChain;
    set<int> nodes;

   
public:
    Gossiper(int Port ,int serverPort);
    ~Gossiper();
    int Gossip();
    void Client(const string& blockChain);
    static Gossiper *getInstance(int Port ,int serverPort);
    static Gossiper *getInstanceExisting();
    virtual void update(const string& setNodes) override;
    string toJson();
    
};