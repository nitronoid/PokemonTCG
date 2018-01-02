#include "testaction.h"
testAction::testAction()
{
}

//-------------------------------------------------------------------
bool testAction::run()
{
        std::cout<<"ACTION"<<'\n';
        // set true because otherwise condition is not fufilled
        return m_status;
}
//-------------------------------------------------------------------
bool actionAddEnergy::run()
{
    std::cout<<"ATTACHED ENERGY"<<'\n';
    m_card.setCurrentEnergy(1);
    return m_status;

}
//-------------------------------------------------------------------
bool actionAddString::run()
{
    std::cout<<m_action<<'\n';
    return m_status;
}
