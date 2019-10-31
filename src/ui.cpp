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
    printBuildingInfo();   
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
    
    std::cout << "-------------------------------------------------" << std::endl;
    std::cout << std::endl << "Time Of Day   : " <<  hh << ":" << mm << std::endl;
    std::cout << std::endl; 
}

void UI::printAmbientTemp()
{
    std::cout << "Ambient Temp. : " <<  double(int(10*(_world->ambientTemperature()-273)))/10 << " C" << std::endl;
    std::cout << std::endl;
}

std::string degreesToWindRose(double direction)
{
    double rotate = direction + 11.25;
    double times1000 = rotate * 1000;
    int truncate = (int) times1000;
    int modulo = truncate % 360000;
    double double_mod = (double) modulo;
    double div1000 = double_mod / 1000;
    int section = (int) (div1000 / 22.5);
    switch (section) {
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
    std::cout << "Solar Heating : " << round(_world->solarRadiationLevel()) << " W/m2, " << degreesToWindRose(_world->azimuthAngle()) << std::endl;
    std::cout << std::endl;
}

std::string UI::tmpP(int i) 
{
    char buffer [5];
    sprintf (buffer, "   %4.1f C", _building->roomTemperature()[i]-273);
    return buffer;
}

std::string UI::winP(int i) 
{
    if (_building->getWindow(i) == window_enum::closed) 
        return " closed  ";
    else 
        return " open    ";
}

std::string UI::htrP(int i) 
{
    if (_building->getHeater(i) == heater_enum::heat_off) 
        return "  off  ";
    else 
        return "  on   ";
}

std::string UI::fanP() 
{
    if (_building->getFan() == fan_enum::fan_off)
        return "   off  ";
    else 
        return "   on   ";
}

void UI::printBuildingInfo()
{
    std::cout << " Room  :  Window : Heater : Fan : Temperature" << std::endl;
    std::cout << " ---      ------   ------   ---   -----------" << std::endl;
    std::cout << " North   " <<  winP(0) << htrP(0) << fanP() << tmpP(0) << std::endl;
    std::cout << " East    " <<  winP(1) << htrP(1) << fanP() << tmpP(1) << std::endl;
    std::cout << " South   " <<  winP(2) << htrP(2) << fanP() << tmpP(2) << std::endl;
    std::cout << " West    " <<  winP(3) << htrP(3) << fanP() << tmpP(3) << std::endl;
    std::cout << std::endl;
}