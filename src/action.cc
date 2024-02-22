#include "action.hh"
#include "generator.hh"

ActionInitialization::ActionInitialization()
{

}

ActionInitialization::~ActionInitialization()
{

}

void ActionInitialization::Build() const
{
    PrimaryGenerator* pg = new PrimaryGenerator();
    SetUserAction(pg);
}