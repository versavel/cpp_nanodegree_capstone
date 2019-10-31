#include <iostream>
#include <math.h>       /* pow */
#include "building.h"

// static constants
static double const kSigma = 5.670374419E-8;  // Stefan–Boltzmann constant, units W m−2 K−4
static double const kRhoAir = 1.225;  // density of air at sea level, in kg m-3
static double const kCpAir = 1000.0;  // specific heat of air at constant pressure, in J kg-1 K-1
static double const kRoomVolume = 950;  // in m2
static double const kRoomWindowArea = 57;  // surface area of the room exposed to the World, in m3
static double const kRoomWindowSolarArea = 36;  // effective surface area of the room exposed to the sun radiation, in m2
static double const kRoom_air_mass = kRhoAir * kRoomVolume; // kg
static double const kRoom_heat_capacity = kCpAir * kRoom_air_mass; // J K-1

static double const alpha_mixing = 0.05;  // fan mixing coefficient
static double const alpha_venting = 0.025; // window venting coefficient

fan_enum Building::getFan()
{
    return _fan_state;
}

heater_enum Building::getHeater(int rm)
{
    return _heater_state[rm];
}

window_enum Building::getWindow(int rm)
{
    return _window_state[rm];
}

void Building::setFan(fan_enum state)
{
    _fan_state = state; 
}

void Building::setHeater(int rm, heater_enum state)
{
    _heater_state[rm] = state;
}

void Building::setWindow(int rm, window_enum state)
{
    _window_state[rm] = state;
}

// return the room temperatures
std::vector<double>  Building::roomTemperature()
{
    return _actual_temperature;
}

// Public method to start simulating the Building environment
void Building::simulate()
{
    updateBuilding();
}

// Private method to simluate the Building environment
void Building::updateBuilding()
{
    // Get current clock value and calculate duration since last update
    _current_clock = _world->clock();
    _interval = _current_clock - _last_clock;

    // Update the room temperatures
    updateActualTemperatures();

    // Update _last_clock
    _last_clock = _current_clock;
}

// Calculate the actual room temperatures
void Building::updateActualTemperatures()
{
    std::vector<double> dt_mixing = deltaTempFanMixing();
    std::vector<double> dt_venting = deltaTempWindowVenting();
    std::vector<double> dt_solar = deltaTempSolar();
    std::vector<double> dt_bb_radiation = deltaTempBlackBodyRadiation();
    std::vector<double> dt_heating = deltaTempHeater();
   
   // Update the room temperatures
   for (int rm = 0; rm < _actual_temperature.size(); rm++) {
        //std::cout << "dt " << dt_mixing[rm] << " | " << dt_venting[rm] << " | " << dt_solar[rm] << " | " << dt_bb_radiation[rm] << std::endl;
        _actual_temperature[rm] += dt_mixing[rm] + dt_venting[rm] + dt_solar[rm] + dt_bb_radiation[rm] + dt_heating[rm]; }
}

// Calculate room temperature change due to mixing by the fan
std::vector<double> Building::deltaTempFanMixing()
{
    // Check if fan is on
    if (_fan_state == fan_enum::fan_off) {
        std::vector<double> dt {0, 0, 0, 0};
        return dt;
    }
    
    // Calculate average room temperature
    double avg_rm_temp = 0;
        for (int rm = 0; rm < _actual_temperature.size(); rm++) {
        avg_rm_temp += _actual_temperature[rm] / 4; }
    
    // Calculate the change in room temperature
    std::vector<double> dt;
    for (int rm = 0; rm < _actual_temperature.size(); rm++) {
        dt.push_back(alpha_mixing * (avg_rm_temp - _actual_temperature[rm])); }

    return dt;
}

// Calculate room temperature change due to 
std::vector<double> Building::deltaTempWindowVenting()
{
    // Calculate the change in room temperature in each room
    std::vector<double> dt;
    for (int rm = 0; rm < _actual_temperature.size(); rm++) {
        if (_window_state[rm] == window_enum::closed) {
            dt.push_back(0); } 
        else {
            dt.push_back(alpha_venting * (_world->ambientTemperature() - _actual_temperature[rm]));} }

    return dt;
}

// Calculate room temperature change due to Solar Radiation
std::vector<double> Building::deltaTempSolar()
{
    double total_dt = _world->solarRadiationLevel() * kRoomWindowSolarArea * _interval / kRoom_heat_capacity; // K

    // split total_dt between the E, S, and W rooms
    std::vector<double> dt {0, 0, 0, 0};
    double ratio = (_world->azimuthAngle() - 90) / 90;
    if (0 < ratio && ratio <= 1) {
        dt[East] = (1-ratio) * total_dt;
        dt[South] = ratio * total_dt; }
    else if (1 < ratio && ratio <= 2) {
        dt[South] = (2-ratio) * total_dt;
        dt[West] = (ratio-1) * total_dt; }

    return dt;
}

// Calculate room temperature change due to Black Body Radiation
std::vector<double> Building::deltaTempBlackBodyRadiation()
{
    std::vector<double> dt;

    for (int rm = 0; rm < _actual_temperature.size(); rm++) {
        double p = kSigma * kRoomWindowArea * (pow(_world->ambientTemperature(), 4) - pow(_actual_temperature[rm], 4)); // W
        double dt_ = p * _interval / kRoom_heat_capacity; // K
        dt.push_back(dt_); }

    return dt;
} 

// Calculate room temperature changes due to the room heaters 
std::vector<double> Building::deltaTempHeater()
{
    // Calculate the change in room temperature in each room
    std::vector<double> dt;
    for (int rm = 0; rm < _actual_temperature.size(); rm++) {
        if (_heater_state[rm] == heater_enum::heat_off) {
            dt.push_back(0); } 
        else {
            dt.push_back(10000 * _interval / kRoom_heat_capacity);} }

    return dt;
}
