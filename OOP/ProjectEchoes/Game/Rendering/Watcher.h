#ifndef WATCHER_H
#define WATCHER_H
#include "../../World/Field.h"
#include "../../Player/Player.h"
#include "CLIRenderer.h"

class Field;
class Renderer;
class Event;

class Watcher{
private:
    Point Current_position;
    Event* Current_event;
    Renderer* R;
public:
    Watcher();
    ~Watcher();
    void update_position(Point New_position);
    void update_event(Event* New_event);

    void call_renderer(Field& Map, Player& Entity);
};
#endif