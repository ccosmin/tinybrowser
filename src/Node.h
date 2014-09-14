#ifndef __NODE_H__
#define __NODE_H__

#include <string>
#include <vector>
#include <map>

class NodeVisitor;

class Node
{
public:
  std::string GetText() const;
  const std::vector<Node*>& GetChildren() const;

  virtual void Accept(NodeVisitor& nodeVisitor) const = 0;
  virtual ~Node();
private:
  std::string m_text;

  std::vector<Node*> m_children;
};

class TextNode : public Node
{
public:
  virtual void Accept(NodeVisitor& nodeVisitor) const;
};

class ElementNode : public Node
{
public:
  virtual void Accept(NodeVisitor& nodeVisitor) const;
private:
  std::map<std::string, std::string> m_attributes;
};

class NodeVisitor
{
public:
  virtual void OnTextNode(const TextNode& textNode) = 0;
  virtual void OnElementNode(const ElementNode& elementNode) = 0;
  virtual ~NodeVisitor();
};

#endif

