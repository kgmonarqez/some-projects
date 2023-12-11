#include "NewGameLog.h"

NewGameLog::NewGameLog(Mechanics& Controller, Field& Map):ObservedController(Controller), ObservedField(Map){
    update();
}

Point NewGameLog::get_position() const{
    return Position;
}

int NewGameLog::get_field_size_x() const{
    return Field_size_x;
}

int NewGameLog::get_field_size_y() const{
    return Field_size_y;
}

void NewGameLog::update(){
    Position = ObservedController.get_position();
    Field_size_x = ObservedField.get_field_size_x();
    Field_size_y = ObservedField.get_field_size_y();
}