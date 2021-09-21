#include "Server.hpp"
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <cstdlib>      // For exit() and EXIT_FAILURE
#include <iostream>     // For cout
#include <unistd.h>     // For read
#include <thread>       // std::thread
#include <map>
#include <stdio.h>
#include <stdlib.h>
//#include <openssl/sha.h>
#include <iomanip>
#include <sstream>
#include <list>
#include <vector>
#include "BlockChain.hpp"
#include "Gossiper.hpp"
#define PORT 9997
using namespace std;
#define myIP "127.0.0.1"
Server *Server::instance = 0;
Server::Server(int* valuePort)
{
  this->port = *valuePort; 
  std::thread th1([this] { this->Bind(); }); //creo un thread che si occupa di hostare il server
  th1.detach();
}
Server::~Server()
{
}

Server *Server::getInstance(int* port)
{
  if (instance == 0)
  {
    instance = new Server(port); // singleton 
  }
  return instance;
}

void Server::Bind() //esponiamo il server 
{

  // Create a socket (IPv4, TCP)
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    std::cout << "Failed to create socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }

  
  sockaddr_in sockaddr;
  sockaddr.sin_family = AF_INET;
  sockaddr.sin_addr.s_addr = INADDR_ANY;
  sockaddr.sin_port = htons(this->port); 

  if (bind(sockfd, (struct sockaddr *)&sockaddr, sizeof(sockaddr)) < 0)
  {
    std::cout << "Failed to bind to port "<<this->port << std::endl;
    exit(EXIT_FAILURE);
  }

  // Start listening. Hold at most 10 connections in the queue
  if (listen(sockfd, 10) < 0)
  {
    std::cout << "Failed to listen on socket. errno: " << errno << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout << "Server ok" << std::endl;

  // Grab a connection from the queue
  auto addrlen = sizeof(sockaddr);
  while (true)
  {
    int connection = accept(sockfd, (struct sockaddr *)&sockaddr, (socklen_t *)&addrlen);
    if (connection < 0)
    {
      std::cout << "Failed to grab connection. errno: " << errno << std::endl;
      exit(EXIT_FAILURE);
    }
    std::thread th3(&Server::Handle, this, &connection);  // creo un nuovo thread che gestisce la connessione
    th3.detach();
  }
}

void Server::Handle(const int *_connection) //gestisce la connessione
{
  char reader1[1];
  auto bytesRead1 = read(*_connection, &reader1, 1); //leggiamo il dato ricevuto dal client in funzione di questo verrà eseguito codice diverso
  int scelta = atoi(reader1);
  if (scelta == 1 ) // riceveremo la blockchain
  {
    char reader3[1024];
    auto bytesRead3 = read(*_connection, &reader3, 1024);
    long long int dimensioni2 = atoi(reader3); //prima le dimensioni della stringa json
    char *reader;
    //char reader[dimensioni2+1];
    try{
      reader=new char[dimensioni2+1];
    }
    catch (const std::bad_alloc&) {
      return;
    }
    
    auto bytesRead = read(*_connection, reader,dimensioni2+1); //leggiamo la blockchain ricevuta dal client
    notifyObservers(reader, scelta); // notifichiamo l'oggetto blockchain 
    delete reader;
    close(*_connection);
  }
  if (scelta == 2) // riceveremo la lista dei nodi partecipanti
  {
    char reader[2048 * 1000];
    auto bytesRead = read(*_connection, &reader, 2048 * 1000); //
    notifyObservers(reader, scelta); ///notifichiamo all'oggetto gossiper che è arrivata la lista dei nodi attivi
    close(*_connection);
  }
  if(scelta == 3)// il cliente vuole la lista dei nodi attivi
  {
    string json = Gossiper::getInstance()->toJson();
    char data[json.length() + 1];
    strcpy(data, json.c_str());
    send(*_connection, data, json.length() + 1, 0); //inviamo la lista dei nodi al client python 
  }
  if(scelta==4)// il client python vuole scrivere una stringa custom sulla blockchain
  {
    char reader[2048 * 1000];
    auto bytesRead = read(*_connection, &reader,2048*1000); // notifichiamo al miner che deve inserire la stringa custom nel blocco che sta minando 

    notifyObservers(reader, scelta);
  }
  else // il client vuole l'intera blockchain per controllare le stringhe customizzate
  {
    string json = BlockChain::getInstance(&this->port)->toJson();
     
    char data[json.length() + 1];
    strcpy(data, json.c_str());
    send(*_connection, data, json.length() + 1, 0); //inviamo il json con la bc al client che ci ha contattato
  }

}
void Server::registerObserver(Observer *observer) // pattern observer 
{
  observers.push_back(observer);
}

void Server::notifyObservers(string reader, int scelta)
{
  for (Observer *observer : observers)
  {
    if (observer->scelta == scelta)  // strategy dentro observer
      observer->update(reader);
  }
}
