#include "Node.h"


std::string Node::GetText() const
{
  return m_text;
}

const std::vector<Node*>& Node::GetChildren() const
{
  return m_children;
}

Node::~Node()
{
}

void TextNode::Accept(NodeVisitor& nodeVisitor) const
{
  nodeVisitor.OnTextNode(*this);
}

void ElementNode::Accept(NodeVisitor& nodeVisitor) const
{
  nodeVisitor.OnElementNode(*this);
}

NodeVisitor::~NodeVisitor()
{
}

