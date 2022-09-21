#include <iostream>
#include <sstream>
#include <semaphore.h>
#include <unordered_map>
#include <vector>

enum INTERFACE_COMMANDS
{
    GREET_COMMAND  
};

class ClientInterface 
{
    public:
        std::vector<std::string> scan_command ();
        void greet_message(void);

    
    private:
        std::vector<std::string> buffer;
};