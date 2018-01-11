#include "condition.h"

Condition::Condition() : Node()
{}
//--------------------------------------------------
bool Condition::execute()
{
    return conditionFunction();
}



