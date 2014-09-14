#ifndef __ATTRIBUTE_H__
#define __ATTRIBUTE_H__

#include <string>

class Attribute
{
public:
  Attribute(const std::string& name, const std::string& value);

  std::string GetName() const;
  std::string GetValue() const;

private:
  std::string m_name;
  std::string m_value;
};

#endif

