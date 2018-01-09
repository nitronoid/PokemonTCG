#include "node.h"
#include "action.h"
#include "sequence.h"

/// #include <chrono>
/// #include <thread>
/// std::this_thread::sleep_for(std::chrono::milliseconds(800));

/// build test tree

int main()
{
    // root node is a Sequence because it is going through a oder
    // attack is the last action you are doing
    Sequence* actionOrder = new Sequence;
    actionOrder->addChild(new Action);
    while(!actionOrder->execute())
        std::cout<<"STOPPED"<<'\n';
    return 0;
}
