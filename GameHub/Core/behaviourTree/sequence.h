#ifndef SEQUENCE_H
#define SEQUENCE_H

#include "compositenode.h"

class Sequence : public compositeNode
{
public:
    ///------------------------------------------------------------------------------
    /// @build default constructor
    ///------------------------------------------------------------------------------
    Sequence();
    ///------------------------------------------------------------------------------
    /// @build execution fucntion override
    ///------------------------------------------------------------------------------
    virtual bool execute() override;
};

#endif // SEQUENCE_H
