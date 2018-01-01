#include "sequence.h"

Sequence::Sequence() : compositeNode()
{

}
//-------------------------------------------------------------------
bool Sequence::run()
{
    // to make them think
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    for(node* child: getChildren())
    {
        if(!child->run())
            return false;
    }
    return true;
}
