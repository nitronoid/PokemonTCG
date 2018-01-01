#ifndef TESTACTION_H
#define TESTACTION_H

#include "node.h"
#include <string>


// leaf node can't add children to this
class testAction : public node
{
public:
    ///-----------------------------------------------------------------
    /// @build copy constructor
    ///-----------------------------------------------------------------
    testAction(std::string _action);
    ///-----------------------------------------------------------------
    /// @build run overwrite function
    ///-----------------------------------------------------------------
    virtual bool run() override;
private:
    ///-----------------------------------------------------------------
    /// @build text based action saying what it does
    ///-----------------------------------------------------------------
    std::string m_action;
};

#endif // TESTACTION_H
