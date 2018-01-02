#include "testaction.h"
testAction::testAction()
{
}

//-------------------------------------------------------------------
bool testAction::run()
{
        std::cout<<m_action<<'\n';
        update();
        // set true because otherwise condition is not fufilled
        return true;
}
//-------------------------------------------------------------------
addEnergyAction::addEnergyAction(int _current, std::string _action)
{
    m_current = _current;
    m_action = _action;
}
//-------------------------------------------------------------------
int addEnergyAction::update()
{
    std::cout<<m_action<<'\n';
    return m_current+=1;
}

