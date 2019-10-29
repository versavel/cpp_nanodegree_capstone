#ifndef BUILDING_H
#define BUILDING_H

#include <vector>
#include "world.h"

enum room {north, east, south, west };
enum on_off {on, off};
enum open_closed { open, closed };

class Building 
{
    /*
    Models the Building the Controller is operating on. 
    The state of the Building is determined by the World and the actions taken by the Controller
    */

    public:
    
    // Constructor and Deconstructors
    Building(World & world): _world(world) {}
    ~Building() {};

    // Getters and Setters
    on_off getFan();
    on_off getHeater();
    open_closed getWindow();
    void setFan(on_off);
    void setHeater(on_off);
    void setWindow(open_closed);
    std::vector<double> getRoomTemperatures();   // return the room temperatures

    // Typical behaviour methods
    void simulate();    // Public method to start simulating the Building environment
    
    private:
    
    // Typical behaviour methods
    void _UpdateBuilding();    // Private method to simluate the Building environment
    void _UpdateActualTemperatures();   // Calculate the actual room temperatures
    std::vector<double> _DeltaTempMixing();// Calculate room temperature change due to mixing
    std::vector<double> _DeltaTempSolar();// Calculate room temperature change due to Solar Radiation 
    std::vector<double> _DeltaTempBlackBodyRadiation();// Calculate room temperature change due to Black Body Radiation 
    
    std::vector<double> _actual_temperature;
    on_off _fan_status;
    std::vector<on_off> _heater_status;
    std::vector<open_closed> _window_status;
    long _last_clock; // clock value of last update, in sec
    long _current_clock; // clock value of current update, in sec
    World _world;
};

#endif