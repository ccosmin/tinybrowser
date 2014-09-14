#ifndef __PARSEHTML_H__
#define __PARSEHTML_H__

#include <string>

class CharStream;

class ParseHtml
{
public:
  ParseHtml(CharStream& stream);

  void Start();

private:
  void ReadElement();
  bool ReadElementEnd(std::string& elementName);
  void ReadAttributes();
  void EatWhitespace();
  std::string ReadString();
  std::string ReadTagName();
  std::string ReadStringNoWs();
  std::string ReadStringWsTrimmed();
  void ReadChildrenNodes(const std::string& parentName);

  CharStream& m_stream;
};

#endif

