#ifndef SELECTOR_H
#define SELECTOR_H

#include "compositenode.h"

class Selector : public compositeNode
{
public:
    ///------------------------------------------------------------------------------
    /// @build default constructor
    ///------------------------------------------------------------------------------
    Selector();
    ///------------------------------------------------------------------------------
    /// @build override execution function
    ///------------------------------------------------------------------------------
    virtual bool execute() override;
};

#endif // SELECTOR_H
