#ifndef CONDITIONLISTEMPTY_H
#define CONDITIONLISTEMPTY_H

#include "condition.h"
#include <vector>
#include <cards.h>

class conditionListEmpty : public Condition
{
public:
    ///---------------------------------------------
    /// @build constructor
    ///---------------------------------------------
    conditionListEmpty(std::vector<Cards> _list);
    ///---------------------------------------------
    /// @build conditionFunctin overwrite
    ///---------------------------------------------
    virtual bool conditionFunction() override;
private:
    /// @build list of cards (can be bench, etc)
    std::vector<Cards> m_list;
};

#endif // CONDITIONLISTEMPTY_H
