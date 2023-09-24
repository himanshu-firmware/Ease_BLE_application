#include "Ease_app_connect.hpp"
#include "Ease_app.h"


int main()
{

    /// first we have to create an object to use that function 

    Ease_device_disc::EASE_DEVICE_DISC ease_dev;

    /// find ease device 
    ease_dev.find_and_connect_ease();

    std::cout << "Connecting to " << ease_dev.identifier().value_or("UNKNOWN") << " ["
              << ease_dev.address().value_or("UNKNOWN") << "]" << std::endl;

    // If the connection wasn't successful, no exception will be thrown.
    bool connect_was_successful = ease_dev.connect();
    if (!connect_was_successful)
    {
        std::cout << "Failed to connect to " << peripheral.identifier().value_or("UNKNOWN") << " ["
                  << peripheral.address().value_or("UNKNOWN") << "]" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Successfully connected, listing services." << std::endl;

        auto services = peripheral.services();

    if (!services.has_value())
    {
        std::cout << "Failed to list services." << std::endl;
        return EXIT_FAILURE;
    }

    for (auto service : *services)
    {
        std::cout << "Service: " << service.uuid() << std::endl;
        for (auto characteristic : service.characteristics())
        {
            std::cout << "  Characteristic: " << characteristic.uuid() << std::endl;

            for (auto &descriptor : characteristic.descriptors())
            {
                std::cout << "  Descriptor: " << descriptor.uuid() << std::endl;
            }
        }
    }
    /// create a new peripheral object 

    

    return 0;
}