#include "condition.h"

Condition::Condition() : Node()
{}

bool Condition::execute()
{
}

energyCondition::energyCondition()
{

}
//--------------------------------------------------
bool energyCondition::execute()
{
    return m_function;
}
