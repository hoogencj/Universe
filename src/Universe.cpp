/**
 * Name: Christopher Hoogenboom
 * VUNet ID: hoogencj
 * email: christopher.j.hoogenboom@vanderbilt.edu
 * I neither gave nor received help on this assignment
 * */
#include "Object.h"
#include <Universe.h>
#include <iostream>

// Iterator typedefs
typedef std::vector<Object*>::iterator iterator;
typedef std::vector<Object*>::const_iterator const_iterator;

Universe* Universe::inst = nullptr;

Universe* Universe::instance()
{
    if (inst == nullptr)
        inst = new Universe();
    return inst;
}

Universe::~Universe()
{
    release(objects);
    inst = nullptr;
}

iterator Universe::begin()
{
    return objects.begin();
}

const_iterator Universe::begin() const
{
    return objects.begin();
}

iterator Universe::end()
{
    return objects.end();
}

const_iterator Universe::end() const
{
    return objects.end();
}

std::vector<Object*> Universe::getSnapshot() const
{
    std::vector<Object*> ret;
    std::for_each(begin(), end(), [&ret](Object* obj) { ret.push_back(obj->clone()); });
    return ret;
}

void Universe::stepSimulation(const double& timeSec)
{
    std::vector<Object*> snap = getSnapshot();
    std::vector<vector2> forceArr(snap.size());
    std::transform(snap.begin() + 1, snap.end(), forceArr.begin() + 1, [&snap](Object* obj) {
        vector2 force;
        std::for_each(snap.begin(), snap.end(),
            [&force, &obj](const Object* j) { force += obj->getForce(*j); });
        return force;
    });
    for (size_t i = 1; i < objects.size(); ++i) {
        snap[i]->setPosition(timeSec
                * (snap[i]->getVelocity()
                      + (timeSec * forceArr[i] / snap[i]->getMass() + snap[i]->getVelocity()))
                / 2
            + snap[i]->getPosition());
        snap[i]->setVelocity(timeSec * forceArr[i] / snap[i]->getMass() + snap[i]->getVelocity());
    }
    swap(snap);
}

void Universe::swap(std::vector<Object*>& snapshot)
{
    std::swap(objects, snapshot);
    release(snapshot);
}

Object* Universe::addObject(Object* ptr)
{
    objects.push_back(ptr);
    return ptr;
}

void Universe::release(std::vector<Object*>& objectsVec)
{
    for (Object* obj : objectsVec)
        delete obj;
    objectsVec.clear();
}
