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
    Controller(std::shared_ptr<World> world, std::shared_ptr<Building> building): _world(world), _building(building) {};
    //~Controller() {};

    // Getters and Setters

    // Typical behaviour methods
    void simulate();    // Public method to start simulating the Controller
    
    private:
    
    // Typical behaviour methods
    void updateController();    // Private method to simluate the Controller
    void updateHeatersAndWindows();    // update whether the heater (on/off) 
                                        // and window (open/closed) in each room
    void updateFan();  // update whether the fan should be on or off
    double averageRoomTemperature();   // return the average room temperature
    double maxBuildingTemperature();   // return the maximum room temperature
    double minBuildingTemperature();   // return the minimum room temperature
    std::shared_ptr<World> _world;
    std::shared_ptr<Building> _building;
};

#endif