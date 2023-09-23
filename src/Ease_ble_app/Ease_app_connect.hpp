#ifndef _EASE_APP_CONNECT_H_
#define _EASE_APP_CONNECT_H_


#include <iostream>
#include <vector>


#define  LOG_I(str, ...)    (std::cout<<str ##__VA_ARGS__ <<std::endl)


namespace Ease_device_disc
{

class EASE_DEVICE_DISC
{
    public:


    /// @brief this return 0 if succesfully connected , also print log messages  
    /// @return 
    int find_and_connect_ease(void);


    /// a function that returns the peripheral type so to use as an objedct 

};
} /// namespace device discovery 

#endif 