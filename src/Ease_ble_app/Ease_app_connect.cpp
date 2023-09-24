#include "Ease_app_connect.hpp"

#include "utils.hpp"



/// @brief  define the peripheral id 
/// @param  void
/// @return periperhal object 
// SimpleBLE::Safe::Peripheral Ease_device_disc::EASE_DEVICE_DISC::get_peripheral_id(void)
// {
//     return this->peri_obj;
// } 

Ease_device_disc::EASE_DEVICE_DISC::EASE_DEVICE_DISC(void)
{
    LOG_I("constructor for easedevice disc");
}

Ease_device_disc::EASE_DEVICE_DISC::~EASE_DEVICE_DISC(void)
{
    LOG_I("desctructor for easedevice disc");
}



int Ease_device_disc::EASE_DEVICE_DISC::find_and_connect_ease(void)
{
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

    return EXIT_SUCCESS;


}


