#pragma once
#include <string>
class Observer {

public:

    int scelta;
    virtual void update(const std::string&) = 0; // funzione virtuale pura(astratta)

};


