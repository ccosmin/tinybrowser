#include <ctype.h>
#include <iostream>
#include <stdio.h>
#include <stdexcept>
#include "ParseHtml.h"
#include "CharStream.h"

ParseHtml::ParseHtml(CharStream& stream)
  : m_stream(stream)
{
}

void ParseHtml::Start()
{
  ReadElement();
}

void ParseHtml::EatWhitespace()
{
  int c;
  while ( (c = m_stream.GetChar()) != EOF )
  {
    if ( ! isspace(c) )
    {
      m_stream.UngetChar(c);
      break;
    }
  } 
}

std::string ParseHtml::ReadString()
{
  std::string str;
  int c;
  while ( (c = m_stream.GetChar()) != EOF )
  {
    if ( ! isspace(c) && c != '>' )
    {
      str += c;
    }
    else
    {
      m_stream.UngetChar(c);
      break;
    }
  } 
  std::cout << "String: " << str << std::endl;
  return str;
}

std::string ParseHtml::ReadStringNoWs()
{
  std::string str;
  int c;
  while ( (c = m_stream.GetChar()) != EOF )
  {
    if ( ! isspace(c) )
    {
      str += c;
    }
    else
    {
      m_stream.UngetChar(c);
      break;
    }
  } 
  std::cout << "String: " << str << std::endl;
  return str;
}

std::string ParseHtml::ReadStringWsTrimmed()
{
  EatWhitespace();

  std::string str;
  int lastNonWs = 0;
  int c;
  int i = 0;
  while ( (c = m_stream.GetChar()) != EOF )
  {
    if ( c == '<' || c == '>' )
    {
      m_stream.UngetChar(c);
      break;
    }
    if ( ! isspace(c) )
      lastNonWs = i;

    str += c;

    ++i;
  } 
  str.resize(lastNonWs + 1);
  std::cout << "String: " << str << std::endl;
  return str;
}

std::string ParseHtml::ReadTagName()
{
  std::string str;
  int c;
  while ( (c = m_stream.GetChar()) != EOF )
  {
    if ( ! isspace(c) && c != '>' && c != '/' )
    {
      str += c;
    }
    else
    {
      m_stream.UngetChar(c);
      break;
    }
  } 
  std::cout << "Tag name: " << str << std::endl;
  return str;
}

void ParseHtml::ReadElement()
{
  EatWhitespace();
  int c = m_stream.GetChar();
  if ( c != '<' )
    throw std::runtime_error("Reading element start expected <");
  std::string name = ReadTagName();
  std::cout << "Element name " << name << std::endl;
  ReadAttributes();
  c = m_stream.GetChar();
  if ( c == '/' )
  {
    EatWhitespace();
    c = m_stream.GetChar(); // This must be '>'
    if ( c != '>' )
      throw std::runtime_error("Reading element end expected >");
  }
  else
  {
    if ( c != '>' )
      throw std::runtime_error("Reading end of element tag expected >");
  }
  ReadChildrenNodes(name);
}

void ParseHtml::ReadChildrenNodes(const std::string& parentName)
{
  EatWhitespace();
  int c = m_stream.GetChar();
  if ( c == '<' )
  {
    m_stream.UngetChar(c);
    std::string elementName;
    while ( elementName != parentName )
    {
      if ( ! ReadElementEnd(elementName) )
      {
        ReadElement();
      }
    }
  }
  else
  {
    m_stream.UngetChar(c);
    std::string textNode = ReadStringWsTrimmed();
  }
}

bool ParseHtml::ReadElementEnd(std::string& elementEnd)
{
  EatWhitespace();
  int c1 = m_stream.GetChar();
  if ( c1 != '<' )
  {
    m_stream.UngetChar(c1);
    return false;
  }
  int c2 = m_stream.GetChar();
  if ( c2 == '/' )
  {
    elementEnd = ReadTagName();
    std::cout << "Element end: " << elementEnd << std::endl;
    EatWhitespace();
    c2 = m_stream.GetChar();
    if ( c2 != '>' )
      throw std::runtime_error("Reading element end expected >");
    return true;
  }
  m_stream.UngetChar(c2);
  m_stream.UngetChar(c1);
  return false;
}

void ParseHtml::ReadAttributes()
{
  EatWhitespace();
  std::string attrName;
  std::string attrValue;
  std::string word;
  int c;
  while ( (c = m_stream.GetChar()) != EOF )
  {
    if ( isspace(c) && ! attrName.empty() )
    {
      attrValue = word;
      EatWhitespace();
      continue;
    }
    if ( c == '>' || c == '/' )
    {
      m_stream.UngetChar(c);
      break;
    }
    if ( c == '=' )
    {
      attrName = word;
      EatWhitespace();
      continue;
    }
    word += c;
  }
}

