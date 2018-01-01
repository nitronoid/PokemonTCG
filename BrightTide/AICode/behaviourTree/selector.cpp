#include "selector.h"

Selector::Selector() : compositeNode()
{

}
//-------------------------------------------------------------------
bool Selector::run()
{
    // to make them think
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    for(node* child: getChildren())
    {
        if(child->run())
            return true;
    }
    return false;
}
