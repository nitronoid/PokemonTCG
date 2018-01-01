#include "compositenode.h"

compositeNode::compositeNode() : node()
{

}
//-------------------------------------------------------------------
void compositeNode::addChild(node *_child)
{
    m_children.push_back(_child);
}
//-------------------------------------------------------------------
std::vector<node*> compositeNode::getChildren()
{
    return m_children;
}
