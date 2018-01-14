#ifndef COMPOSITENODE_H
#define COMPOSITENODE_H

#include "node.h"
#include <vector>

class compositeNode : public Node
{
public:
    ///------------------------------------------------------------------------------
    /// @build default constructor
    ///------------------------------------------------------------------------------
    compositeNode();
    ///------------------------------------------------------------------------------
    /// @build get function of list of function
    ///------------------------------------------------------------------------------
    std::vector<Node*> getChildren();
    ///------------------------------------------------------------------------------
    /// @build add childruren function
    ///------------------------------------------------------------------------------
    void addChild(Node* _child);
private:
    ///------------------------------------------------------------------------------
    /// @build list of children
    ///------------------------------------------------------------------------------
    std::vector<Node*> m_children;
};

#endif // COMPOSITENODE_H
