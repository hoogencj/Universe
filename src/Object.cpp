/**
 * Name: Christopher Hoogenboom
 * VUNet ID: hoogencj
 * email: christopher.j.hoogenboom@vanderbilt.edu
 * I neither gave nor received help on this assignment
 * */
#include <Object.h>
#include <Universe.h>
#include <Visitor.h>

Object::Object(const std::string& name, double mass, const vector2& pos, const vector2& vel)
    : name(name)
    , mass(mass)
    , position(pos)
    , velocity(vel)
{
}

void Object::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

Object* Object::clone() const
{
    return new Object(name, mass, position, velocity);
}

double Object::getMass() const noexcept
{
    return mass;
}

std::string Object::getName() const noexcept
{
    return name;
}

vector2 Object::getPosition() const noexcept
{
    return position;
}

vector2 Object::getVelocity() const noexcept
{
    return velocity;
}

vector2 Object::getForce(const Object& rhs) const noexcept
{
    if ((rhs.getPosition() - getPosition()).norm() != 0) {
        return (rhs.getPosition() - getPosition()).normalize() * Universe::G * getMass()
            * rhs.getMass() / (rhs.getPosition() - getPosition()).normSq();
    } else
        return vector2();
}

void Object::setPosition(const vector2& pos)
{
    position = pos;
}

void Object::setVelocity(const vector2& vel)
{
    velocity = vel;
}

bool Object::operator==(const Object& rhs) const
{
    return getName() == rhs.getName() && getMass() == rhs.getMass()
        && getPosition() == rhs.getPosition() && getVelocity() == rhs.getVelocity();
}

bool Object::operator!=(const Object& rhs) const
{
    return !(*this == rhs);
}