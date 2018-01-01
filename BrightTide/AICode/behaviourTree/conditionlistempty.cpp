#include "conditionlistempty.h"

conditionListEmpty::conditionListEmpty(std::vector<Cards> _list)
{
    m_list = _list;
}
//-------------------------------------------------------------------
bool conditionListEmpty::conditionFunction()
{
    // checks if the list is not empty
    if(m_list.size() != 0)
    {
        m_result = true;
    }
    return m_result;
}
