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

protected:
    ///-----------------------------------------------------------------
    /// @build text based action saying what it does
    ///-----------------------------------------------------------------
    bool m_status = true;
};
//-------------------------------------------------------------------
class actionAddEnergy : public testAction
{
public:
    actionAddEnergy(Cards _card){m_card = _card;}
    virtual bool run() override;
private:
    Cards m_card;
};
//-------------------------------------------------------------------
class actionAddString : public testAction
{
public:
    actionAddString(std::string _action){m_action = _action;}
    virtual bool run() override;
private:
    std::string m_action;
};

#endif // TESTACTION_H
