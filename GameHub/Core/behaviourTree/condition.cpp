#include "condition.h"

Condition::Condition() : Node()
{}

energyCondition::energyCondition(bool function)
{
    m_function = function;
}
//--------------------------------------------------
bool Condition::execute()
{
    return conditionFunction();
}
//--------------------------------------------------
bool energyCondition::conditionFunction()
{
    return m_function;
}
//--------------------------------------------------
