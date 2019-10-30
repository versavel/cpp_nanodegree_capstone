#include <iostream>
#include <stdlib.h>  // used by std::ldiv, std::ldiv_t
#include "ui.h"


// Public method to start the User Interface
void UI::simulate()
{
    updateUI();
}

// Private method to simluate the User Interface
void UI::updateUI()
{
    printTimeOfDay();
    printAmbientTemp();
    printSolarInfo();
    printRoomTemperatures();
}

void UI::printTimeOfDay()
{
    std::string hh, mm;
    std::ldiv_t divresult;

    divresult = std::ldiv(int(_world->timeOfDay()), 3600);
    int h = divresult.quot;
    if (h<10) 
        hh = "0" + std::to_string(h);
    else
        hh = std::to_string(h);

    divresult = std::ldiv(divresult.rem, 60);
    int m = divresult.quot;
    if (m<10) 
        mm = "0" + std::to_string(m);
    else
        mm = std::to_string(m);
    
    std::cout << "         Time Of Day : " <<  hh << ":" << mm << std::endl; 
}

void UI::printAmbientTemp()
{
    std::cout << "Ambient Temperature  : " <<  double(int(10*(_world->ambientTemperature()-273)))/10 << " C" << std::endl;
}

std::string degreesToWindRose(double direction)
{
    switch ((int) (direction/16)) {
        case 4: return "E";
        case 5: return "ESE";
        case 6: return "SE";
        case 7: return "SSE";
        case 8: return "S";
        case 9: return "SSW";
        case 10: return "SW";
        case 11: return "WSW";
        case 12: return "W";
        default: return "Nite"; }
}

void UI::printSolarInfo() 
{
    std::cout << "     Solar Radiation : " << round(_world->solarRadiationLevel()) << " W/m2, " << degreesToWindRose(_world->azimuthAngle()) << std::endl;
}

void UI::printRoomTemperatures()
{
    std::cout << "   Room Temperature" << std::endl;
    std::cout << "               North : " <<  double(int(10*(_building->roomTemperature(room_enum::North)-273)))/10 << " C" << std::endl;
    std::cout << "               East  : " <<  double(int(10*(_building->roomTemperature(room_enum::East)-273)))/10 << " C" << std::endl;
    std::cout << "               South : " <<  double(int(10*(_building->roomTemperature(room_enum::South)-273)))/10 << " C" << std::endl;
    std::cout << "               West  : " <<  double(int(10*(_building->roomTemperature(room_enum::West)-273)))/10 << " C" << std::endl;
}