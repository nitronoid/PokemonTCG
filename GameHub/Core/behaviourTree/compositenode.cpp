#include "compositenode.h"

compositeNode::compositeNode() : Node()
{

}
//--------------------------------------------------
std::vector<Node*> compositeNode::getChildren()
{
    return m_children;
}
//--------------------------------------------------
void compositeNode::addChild(Node *_child)
{
    m_children.push_back(_child);
}
