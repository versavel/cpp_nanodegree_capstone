#ifndef UI_H
#define UI_H

#include <memory>
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
    UI(std::shared_ptr<World> world, std::shared_ptr<Building> building, std::shared_ptr<Controller> controller): 
        _world(world), _building(building), _controller(controller) {};
    ~UI() {};

    // Getters and Setters

    // Typical behaviour methods
    void simulate();    // Public method to start the User Interface
    
    private:
    // Typical behaviour methods
    void updateUI();    // Private method to simluate the User Interface
    void printTopSection();
    void printBottomSection();
    std::string ambP();
    std::string winP(int i);
    std::string tmpP(int i);
    std::string htrP(int i);
    std::string fanP();

    std::shared_ptr<World> _world;
    std::shared_ptr<Building> _building;
    std::shared_ptr<Controller> _controller;
};

#endif