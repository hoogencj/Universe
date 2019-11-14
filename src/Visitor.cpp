/**
 * Name: Christopher Hoogenboom
 * VUNet ID: hoogencj
 * email: christopher.j.hoogenboom@vanderbilt.edu
 * I neither gave nor received help on this assignment
 * */

#include <Object.h>
#include <Visitor.h>

PrintVisitor::PrintVisitor(std::ostream& os)
    : os(os)
{
}

void PrintVisitor::visit(Object& object)
{
    os << object.getName();
}