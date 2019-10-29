#ifndef UI_H
#define UI_H

#include "world.h"
#include "building.h"
#include "controller.h"

class UI 
{
    /*
    The UI, or User Interface, prints out the value of some of the Building and World objects
    */

    public:
    
    // Constructor and Deconstructors
    UI(World &world, Building &building, Controller &controller): _world(world), _building(building), _controller(controller) {};
    ~UI() {};

    // Getters and Setters

    // Typical behaviour methods
    void simulate();    // Public method to start the User Interface
    
    private:
    // Typical behaviour methods
    void _UpdateUI();    // Private method to simluate the User Interface

    World _world;
    Building _building;
    Controller _controller;
};

#endif