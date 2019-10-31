#include <algorithm>    // std::min_element, std::max_element
#include "controller.h"

static double const t_target = 273 + 20;  // Target temperature for each room in the building, Units: K
static double const alpha = 2;  // threshold value for controlling the heaters and windows, Units: degree K
static double const beta = 1;  // threshold value for controlling the fan, Units: degree K

// Public method to start simulating the Controller
double Controller::targetTemperature() {
    return t_target;
}

void Controller::simulate()
{
    updateController();
}
    
// Private method to simluate the Controller
void Controller::updateController()
{
    updateHeatersAndWindows();
    updateFan();
}

// decide whether to turn on/off the heater and open/close the window in each room
void Controller::updateHeatersAndWindows()
{
    double t_avg = averageRoomTemperature();
    if (t_avg > t_target + alpha) {
        for (int i = 0; i < 4; i++) {
            if (_building->roomTemperature()[i] > t_target ) {
                _building->setWindow(i, window_enum::open); } }
    } else if (t_avg < t_target) {
        for (int i = 0; i < 4; i++) {
            if (_building->roomTemperature()[i] < t_target ) {
                _building->setHeater(i, heater_enum::heat_on); } }
    } else {
        for (int i = 0; i < 4; i++) {
           _building->setWindow(i, window_enum::closed);
           _building->setHeater(i, heater_enum::heat_off); }
    }
}
// update whether the fan should be on or off
void Controller::updateFan()
{
    double delta_t = maxBuildingTemperature() - minBuildingTemperature();
    if (delta_t > beta) {
        _building->setFan(fan_enum::fan_on); 
    } else {
        _building->setFan(fan_enum::fan_off);
    }
}

// return the average room temperature
double Controller::averageRoomTemperature()
{
    double average {0};
    for (int rm = 0; rm < 4; rm++) {
        average += _building->roomTemperature()[rm] / 4; }
    return average;
}

// return the maximum room temperature
double Controller::maxBuildingTemperature()
{
    double x{0};
    for (int rm = 0; rm < 4; rm++) {
        if (_building->roomTemperature()[rm] > x) x = _building->roomTemperature()[rm]; }
    return x;
}

// return the minimum room temperature
double Controller::minBuildingTemperature()
{
    double x{10000};
    for (int rm = 0; rm < 4; rm++) {
        if (_building->roomTemperature()[rm] < x) x = _building->roomTemperature()[rm]; }
    return x;
}