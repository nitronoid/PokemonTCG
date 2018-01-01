#include "testaction.h"
testAction::testAction(std::__1::string _action)
{
    m_action = _action;
}
//-------------------------------------------------------------------
bool testAction::run()
{
        std::cout<<m_action<<'\n';
        // set true because otherwise condition is not fufilled
        return true;
}
