#include "sequence.h"

Sequence::Sequence() : compositeNode()
{

}
//--------------------------------------------------
bool Sequence::execute()
{
    for(Node* child : getChildren())
    {
        if(!child->execute())
            return false;
    }
    return true;
}
//--------------------------------------------------
