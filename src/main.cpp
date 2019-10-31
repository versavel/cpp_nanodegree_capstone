#include <iostream>
#include <thread>
#include <chrono>

#include "world.h"
#include "building.h"
#include "controller.h"
#include "ui.h"

int main() {
    
    // set simulation time step
    long time_step = 5 * 60; // seconds

    // declare class instances
    std::shared_ptr<World> world (new World(time_step));
    std::shared_ptr<Building> building (new Building(world));
    std::shared_ptr<Controller> controller (new Controller(world, building));
    std::shared_ptr<UI> ui (new UI(world, building, controller));

    while(true)
    {
        world->simulate();
        building->simulate();
        controller->simulate();
        if (world->timeOfDay() % 3600 == 0) {
            ui->simulate(); }
        
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
    }
    return 0;
}