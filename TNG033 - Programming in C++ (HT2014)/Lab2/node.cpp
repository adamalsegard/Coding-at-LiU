
#include "node.h"

Node::Node (int nodeVal, Node *nextPtr)
 : value (nodeVal), next (nextPtr)
{
    //cout << "Constructor Node" << std::endl;
}

