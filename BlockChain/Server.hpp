#include <thread>
#include <map>
#include <iostream>
#include <cassert>
#include <list>
#include <vector>
#include "Subject.hpp"
#define myIP "127.0.0.1"

using namespace std;
class Server : Subject 
{
private:
    int port;
    static Server *instance;
    std::vector<Observer *> observers;

public:
    Server(int* valuePort);
    void Bind();
    ~Server();
    void Handle(const int *connection);
    static Server *getInstance(int* port);
    void registerObserver(Observer *observer) override;
    void notifyObservers(string,int) override;
};