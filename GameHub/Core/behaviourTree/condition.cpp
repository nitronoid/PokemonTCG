#include "condition.h"

Condition::Condition(bool _function) : Node()
{
    m_function = _function;
}

bool Condition::execute()
{
    return m_function;
}
