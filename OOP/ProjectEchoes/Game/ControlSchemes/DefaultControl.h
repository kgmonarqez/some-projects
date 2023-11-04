#include "ControlScheme.h"

class DefaultControl: public ControlScheme{
private:
    enum class DefaultCommands{
        LEFT = 'a',
        RIGHT = 'd',
        UP = 'w',
        DOWN = 's'
    };
    std::map<CommandNames, Command*> ControlCommands;
public:
    DefaultControl();
    std::map<CommandNames, Command*> GetControlCommands();
    bool is_initialised();
    ~DefaultControl();
};