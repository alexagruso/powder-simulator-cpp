#include "event.hpp"

#include <iostream>
#include <string>

using namespace ps;

sys::EventType sys::Event::getType() const
{
    return this->type;
}

void sys::Event::perform(std::string message)
{
    std::cout << "performed event " << message << '\n';
}