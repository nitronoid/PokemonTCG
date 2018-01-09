#include "selector.h"

Selector::Selector() : compositeNode()
{}
//--------------------------------------------------
bool Selector::execute()
{
    for(Node* child : getChildren())
    {
        if(child->execute())
        {
            return true;
        }
        return false;
    }
}
//--------------------------------------------------
