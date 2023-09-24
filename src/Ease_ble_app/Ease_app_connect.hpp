#ifndef _EASE_APP_CONNECT_H_
#define _EASE_APP_CONNECT_H_


#include <iostream>
#include <vector>

#include "simpleble/SimpleBLE.h"

#define  LOG_I(str, ...)    printf(str ##__VA_ARGS__ "\r\n")


namespace Ease_device_disc
{

class EASE_DEVICE_DISC : public SimpleBLE::Peripheral 
{
    public:

    /// @brief constructors 
    /// @param  
    EASE_DEVICE_DISC(void);

    /// @brief desctructor 
    /// @param  
    ~EASE_DEVICE_DISC(void);

    /// @brief this return 0 if succesfully connected , also print log messages  
    /// @return 
    int find_and_connect_ease(void);

    /// a function that returns the peripheral type so to use as an objedct 

};
} /// namespace device discovery 

#endif 