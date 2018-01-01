#include "condition.h"

Condition::Condition(bool _func)
{
    m_func = _func;
}
//-------------------------------------------------------------------
bool Condition::run()
{
    // you should make a method that returns a condition
    // if certain condition returns true return true
    // else return false
    // to make them think
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    // return condition
    return m_func;
}
