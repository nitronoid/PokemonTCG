#include "action.h"
Action::Action() : Node()
{}
//-------------------------------------------------------
bool Action::execute()
{
    std::cout<<"ACTION"<<'\n';
    return true;
}
//-------------------------------------------------------
bool testAction::execute()
{

}
