#include "action.h"
Action::Action(bool _action)
{
    m_action = _action;
}
//-------------------------------------------------------
bool Action::execute()
{
    return m_action;
}
//-------------------------------------------------------
