#include "Ease_app_connect.hpp"
#include "Ease_app.h"


#include "utils.hpp"

#include<Windows.h>
#include<fileapi.h>


void eeg_notif_callback(SimpleBLE::ByteArray bytes);

void battery_notif_callback(SimpleBLE::ByteArray bytes);

void connected_callback(void);
void disconnected_callback(void);


int main()
{

    // HANDLE file_handle = CreateFileA( , GENERIC_WRITE, FILE_SHARE_WRITE,)
    /// first we have to create an object to use that function 

    // Ease_device_disc::EASE_DEVICE_DISC ease_dev;

    // /// find ease device 
    // ease_dev.find_and_connect_ease();

        // if ( SimpleBLE::Safe::Adapter::bluetooth_enabled())
    // {
    //     LOG_I("BLuetooth is off please turn it on");
    //     return EXIT_FAILURE;
    // }

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

    /// create a list of peripheral object of class below that would be scanned by the adapter 
    std::vector<SimpleBLE::Safe::Peripheral> peripherals;


    /// prepare the adapter to scan for devices 
    adapter.set_callback_on_scan_found([&](SimpleBLE::Safe::Peripheral peripheral)
                                       {
        std::cout << "Found device: " << peripheral.identifier().value_or("UNKNOWN") << " ["
                  << peripheral.address().value_or("UNKNOWN") << "]" << std::endl;
        peripherals.push_back(peripheral); }
        );

    adapter.set_callback_on_scan_start([](void)
                                       { std::cout << "Scan started." << std::endl; });
    adapter.set_callback_on_scan_stop([](void)
                                      { std::cout << "Scan stopped." << std::endl; });
    // Scan for 5 seconds and return.
    adapter.scan_for(5000);


    //// scan finished now search for device name EASE 
    int Ease_index =-1;
    for (size_t i = 0; i < peripherals.size(); i++)
    {
        if( peripherals[i].identifier().value_or("UNKNOWN") == "EASE")
        {
            Ease_index =i;
            break;
        }
        std::cout << "[" << i << "] " << peripherals[i].identifier().value_or("UNKNOWN") << " ["
                  << peripherals[i].address().value_or("UNKNOWN") << "]" << std::endl;
    }

    if(Ease_index == -1)
    {
        //// failed to serach the EASE
        LOG_I("Ease device not found in the list ");
        return EXIT_FAILURE;
    }
    // auto selection = Utils::getUserInputInt("Please select a device to connect to", peripherals.size() - 1);
    // if (!selection.has_value())
    // {
    //     return EXIT_FAILURE;
    // }
    // peripheral.disconnect();

    SimpleBLE::Safe::Peripheral peripheral = peripherals[Ease_index];

    /// set the callbacks 
    peripheral.set_callback_on_connected(connected_callback);
    peripheral.set_callback_on_disconnected(disconnected_callback);


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

    //// create a file to save battery data 
  

    /// get the battery service and char uuid 

    // peripheral.notify( , ,battery_notif_callback);
    // peripheral.notify(, , eeg_notif_callback);


    ///suscribe for the notification and turn on file reading 


    /// wait for the device disconnection     

    return 0;
}


void battery_notif_callback(SimpleBLE::ByteArray bytes)
{
        std::cout << "Received: batt data";
        Utils::print_byte_array(bytes);
} 

void eeg_notif_callback(SimpleBLE::ByteArray bytes)
{
        std::cout << "Received: EEG data";
        Utils::print_byte_array(bytes);
}


void __cdecl connected_callback(void)
{
    LOG_I("connected Ease device");
}

void __cdecl disconnected_callback(void)
{
    LOG_I("disconnected Ease device");
}
