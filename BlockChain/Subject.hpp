
#pragma once
#include "Observer.hpp"

/**
 * Interface for the Subject
 */
class Subject {

public:

    /**
     * Register an observer
     
     */
    virtual void registerObserver(Observer *observer) = 0; // virtuale pura(astratta)
   

    /**
     * Notify all the registered observers when a change happens
     */
    virtual void notifyObservers(std::string,int ) = 0; //virtuale pura (astratta)

};


