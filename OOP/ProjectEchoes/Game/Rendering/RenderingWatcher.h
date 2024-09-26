#ifndef WATCHER_H
#define WATCHER_H
#include "../../World/Field.h"
#include "../../Player/Player.h"
#include "CLIRenderer.h"

class Field;
class Renderer;
class Event;

class RenderingWatcher{
private:
    std::list<MechanicsObserver*> Mechanics_observers;

    Point Current_position;
    Event* Current_event;
    int Current_hp;
    
    Renderer* R;
public:
    RenderingWatcher();
    ~RenderingWatcher();
    
    void update_position(Point New_position);
    void update_event(Event* New_event);
    void update_hp(int New_hp);

    void call_renderer(Field& Map);
};
#endif