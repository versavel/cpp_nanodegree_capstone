#ifndef BUILDING_H
#define BUILDING_H

#include <iostream>
#include <math.h>
#include <vector>
#include "world.h"

enum room_enum {North, East, South, West};
enum fan_enum {fan_on, fan_off};
enum heater_enum {heat_on, heat_off};
enum window_enum {open, closed};

class Building 
{
    /*
    Models the Building the Controller is operating on. 
    The state of the Building is determined by the World and the actions taken by the Controller
    */

    public:
    
    // Constructor and Deconstructors
    Building(std::shared_ptr<World> world): _world(world)
    {
        _fan_state = fan_enum::fan_off;
        for (int i=0; i < 4; i++ ) _heater_state.push_back(heater_enum::heat_off);
        for (int i=0; i < 4; i++ ) _window_state.push_back(window_enum::closed);
        for (int i=0; i < 4; i++ ) _actual_temperature.push_back(273+20+pow(-1,i)*5*i);
        _last_clock = _world->clock();
        _current_clock = _world->clock();
        _interval = 0;
    };
    
    ~Building() {};

    // Getters and Setters
    fan_enum getFan();
    heater_enum getHeater(int);
    window_enum getWindow(int);
    void setFan(fan_enum);
    void setHeater(int, heater_enum);
    void setWindow(int, window_enum);
    std::vector<double>  roomTemperature();   // return the room temperatures

    // Typical behaviour methods
    void simulate();    // Public method to start simulating the Building environment
    
    private:
    
    // Typical behaviour methods
    void updateBuilding();    // Private method to simluate the Building environment
    void updateActualTemperatures();   // Calculate the actual room temperatures
    std::vector<double> deltaTempFanMixing();// Calculate room temperature changes due to air mixing by the fan
    std::vector<double> deltaTempWindowVenting();// Calculate room temperature changes due to venting through the open windows
    std::vector<double> deltaTempSolar();// Calculate room temperature changes due to Solar Radiation 
    std::vector<double> deltaTempBlackBodyRadiation();// Calculate room temperature changes due to Black Body Radiation 
    std::vector<double> deltaTempHeater();// Calculate room temperature changes due to the room heaters 
    
    std::vector<double> _actual_temperature;
    fan_enum _fan_state;
    std::vector<heater_enum> _heater_state;
    std::vector<window_enum> _window_state;
    long _last_clock; // clock value of last update, in sec
    long _current_clock; // clock value of current update, in sec
    long _interval; // time between last two clock updates, in sec
    std::shared_ptr<World> _world;
};

#endif