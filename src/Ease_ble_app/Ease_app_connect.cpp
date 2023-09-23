#include "Ease_app_connect.hpp"

#include "utils.hpp"

#include "simpleble/SimpleBLE.h"

int Ease_device_disc::EASE_DEVICE_DISC::find_and_connect_ease(void)
{
    ////////================================================================== get the adapters 
    /// first scan the adapters and get one 
    auto adapter_list = SimpleBLE::Safe::Adapter::get_adapters();
     
    if (!adapter_list.has_value())
    {
        LOG_I(" Failed to list adapters");
        return EXIT_FAILURE;
    }

    if (adapter_list->empty())
    {
        LOG_I("No adapter was found");
        return EXIT_FAILURE;
    }

    // std::cout << "Available adapters: \n";
    // int i = 0;
    // for (auto &adapter : *adapter_list)
    // {
    //     std::cout << "[" << i++ << "] " << adapter.identifier().value() << " [" << adapter.address().value() << "]"
    //               << std::endl;
    // }


    // auto adapter_selection = Utils::getUserInputInt("Please select an adapter", adapter_list->size() - 1);
    // if (!adapter_selection.has_value())
    // {
    //     return EXIT_FAILURE;
    // }

    /// make a refrence to the adapter at the list of 1 item 
    SimpleBLE::Safe::Adapter &adapter = adapter_list->at(0);

    std::vector<SimpleBLE::Safe::Peripheral> peripherals;

    adapter.set_callback_on_scan_found([&](SimpleBLE::Safe::Peripheral peripheral)
                                       {
        std::cout << "Found device: " << peripheral.identifier().value_or("UNKNOWN") << " ["
                  << peripheral.address().value_or("UNKNOWN") << "]" << std::endl;
        peripherals.push_back(peripheral); });

    adapter.set_callback_on_scan_start([]()
                                       { std::cout << "Scan started." << std::endl; });
    adapter.set_callback_on_scan_stop([]()
                                      { std::cout << "Scan stopped." << std::endl; });
    // Scan for 5 seconds and return.
    adapter.scan_for(5000);





}

int main()
{

   

    
    std::cout << "The following devices were found:" << std::endl;
    for (size_t i = 0; i < peripherals.size(); i++)
    {
        std::cout << "[" << i << "] " << peripherals[i].identifier().value_or("UNKNOWN") << " ["
                  << peripherals[i].address().value_or("UNKNOWN") << "]" << std::endl;
    }

    auto selection = Utils::getUserInputInt("Please select a device to connect to", peripherals.size() - 1);
    if (!selection.has_value())
    {
        return EXIT_FAILURE;
    }

    auto peripheral = peripherals[selection.value()];
    std::cout << "Connecting to " << peripheral.identifier().value_or("UNKNOWN") << " ["
              << peripheral.address().value_or("UNKNOWN") << "]" << std::endl;

    // If the connection wasn't successful, no exception will be thrown.
    bool connect_was_successful = peripheral.connect();
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
    peripheral.disconnect();
    return EXIT_SUCCESS;
}
