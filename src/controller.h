#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "world.h"
#include "building.h"

class Controller 
{
    /*
    Models a very simple controller
    */

    public:
    
    // Constructor and Deconstructors
    Controller(World &world, Building &building): _world(world), _building(building) {};
    ~Controller() {};

    // Getters and Setters

    // Typical behaviour methods
    void simulate();    // Public method to start simulating the Controller
    
    private:
    
    // Typical behaviour methods
    void _UpdateController();    // Private method to simluate the Controller
    void _UpdateHeatersAndWindows();    // update whether the heater (on/off) 
                                        // and window (open/closed) in each room
    void _UpdateFan();  // update whether the fan should be on or off
    double averageRoomTemperature();   // return the average room temperature
    double maxBuildingTemperature();   // return the maximum room temperature
    double minBuildingTemperature();   // return the minimum room temperature
    World _world;
    Building _building;
};

#endif