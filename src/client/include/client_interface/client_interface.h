#include <iostream>
#include <sstream>
#include <semaphore.h>

enum INTERFACE_COMMANDS
{
    GREET_COMMAND  
};

class ClientInterface 
{
    public:
        std::string scan_command ();
        void greet_message(void);
        int attach_reader(std::stringstream* __S);
        int start_read(void);
        int end_read(void);
    
    private:
        std::stringstream* strPtr;
};