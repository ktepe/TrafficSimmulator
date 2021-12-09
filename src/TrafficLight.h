#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H
//DONE
#include <mutex>
#include <deque>
#include <condition_variable>
#include "TrafficObject.h"
#include <random>

// forward declarations to avoid include cycle
class Vehicle;

enum TrafficLightPhase {red, green};

class myRand
{
public:
    static int myrand()
    {
        static std::mt19937 rnd_dev;
      
        std::uniform_real_distribution<double> uni_dist(4.0, 6.0);

        return int(uni_dist(rnd_dev)*1000);
       

        //return k;
    }
          
};
     


// FP.3 Define a class „MessageQueue“ which has the public methods send and receive. 
// Send should take an rvalue reference of type TrafficLightPhase whereas receive should return this type. 
// Also, the class should define an std::dequeue called _queue, which stores objects of type TrafficLightPhase. 
// Also, there should be an std::condition_variable as well as an std::mutex as private members. 
template <class T>
class MessageQueue
{
public:
    void send(T &&msg);
    T receive();
    ~MessageQueue();
private:
    std::deque<T> _queue;
    std::mutex _mutex;
    std::condition_variable _cond;
};

// FP.1 : (A) Define a class „TrafficLight“ which is a child class of TrafficObject. 
// The class shall have the public methods „void waitForGreen()“ and „void simulate()“ 
// as well as „TrafficLightPhase getCurrentPhase()“, where TrafficLightPhase is an enum that 
// can be either „red“ or „green“. Also, add the private method „void cycleThroughPhases()“. 
// Furthermore, there shall be the private member _currentPhase which can take „red“ or „green“ as its value. 

class TrafficLight : public TrafficObject
{
public:
    // constructor / desctructor
    TrafficLight();
    ~TrafficLight();
    // getters / setters
    void setCurrentPhase(TrafficLightPhase phase) {_currentPhase = phase ;}; //may not be used 
    TrafficLightPhase getCurrentPhase();
    // typical behaviour methods
    void simulate ();
    void waitForGreen ();
    
private:
    // typical behaviour methods
    void cycleThroughPhases ();
    // FP.4b : create a private member of type MessageQueue for messages of type TrafficLightPhase 
    // and use it within the infinite loop to push each new TrafficLightPhase into it by calling 
    // send in conjunction with move semantics.
    TrafficLightPhase _currentPhase;
    MessageQueue<TrafficLightPhase> _messageQueue;
    std::condition_variable _condition;
    std::mutex _mutex;
    //myRand _rnd;
};

#endif

