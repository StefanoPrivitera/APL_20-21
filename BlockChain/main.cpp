
#include "Node.hpp"
#include <unistd.h>
#include <thread>
#include <iostream>
#include <string.h>
#include <stdio.h>
#define myIP "127.0.0.1"

using namespace std;

int main(int argc, char *argv[])
{
    cout<<"Inserisci il numero della porta da esporre"<<endl;
    int server;
    std::cin >> server;
    cout<<"Inserisci il numero della porta di un nodo attivo "<<endl;
    int client;
    std::cin >> client;
    Node *node=new Node(server,client);
}