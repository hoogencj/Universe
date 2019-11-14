/**
 * Name: Christopher Hoogenboom
 * VUNet ID: hoogencj
 * email: christopher.j.hoogenboom@vanderbilt.edu
 * I neither gave nor received help on this assignment
 * */
#include <Object.h>
#include <ObjectFactory.h>
#include <Universe.h>

Object* ObjectFactory::makeObject(
    std::string name, double mass, const vector2& pos, const vector2& vel)
{
    Object* ptr = new Object(name, mass, pos, vel);
    Universe::instance()->addObject(ptr);
    return ptr;
}