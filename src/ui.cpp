#include <iostream>
#include <stdlib.h>  // used by std::ldiv, std::ldiv_t
#include "ui.h"


// Public method to start the User Interface
void UI::simulate()
{
    _UpdateUI();
}

// Private method to simluate the User Interface
void UI::_UpdateUI()
{
    _PrintTimeOfDay();
    _PrintAmbientTemp();
    
}

void UI::_PrintTimeOfDay()
{
    std::string hh, mm;
    std::ldiv_t divresult;

    divresult = std::ldiv(int(_world->TimeOfDay()), 3600);
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
    
    std::cout << "Time Of Day: " <<  hh << ":" << mm << std::endl; 
}

void UI::_PrintAmbientTemp()
{
    std::cout << "Ambient Temperature (C): " <<  double(int(10*(_world->AmbientTemperature()-273)))/10 << std::endl;
}