#ifndef TESTACTION_H
#define TESTACTION_H

#include "node.h"
#include "cards.h"
#include <string>


// leaf node can't add children to this
class testAction : public node
{
public:
    ///-----------------------------------------------------------------
    /// @build copy constructor
    ///-----------------------------------------------------------------
    testAction();
    ///-----------------------------------------------------------------
    /// @build run overwrite function
    ///-----------------------------------------------------------------
    virtual bool run() override;
    virtual int update() = 0;

protected:
    ///-----------------------------------------------------------------
    /// @build text based action saying what it does
    ///-----------------------------------------------------------------
    std::string m_action;
    int m_current;
};
//-------------------------------------------------------------------
class addEnergyAction : public testAction
{
public:
    addEnergyAction(int _current, std::__1::string _action);
    virtual int update() override;
};
//-------------------------------------------------------------------
class addStringAction : public testAction
{
public:
    addStringAction(std::string _string);
    virtual int update() override;
};

#endif // TESTACTION_H
