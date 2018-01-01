#ifndef COMPOSITENODE_H
#define COMPOSITENODE_H

#include "node.h"
#include <vector>

class compositeNode : public node
{
public:
    ///----------------------------------------------------------------
    /// @build constructor
    ///----------------------------------------------------------------
    compositeNode();
    ///-----------------------------------------------------------------
    /// @build list of children
    ///-----------------------------------------------------------------
    std::vector<node*> getChildren();
    ///-----------------------------------------------------------------
    /// @build add children function
    ///-----------------------------------------------------------------
    void addChild(node* _child);
private:
    ///-----------------------------------------------------------------
    /// @build list of children
    ///-----------------------------------------------------------------
    std::vector<node*> m_children;
};

#endif // COMPOSITENODE_H
