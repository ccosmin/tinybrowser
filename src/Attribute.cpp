#include "Attribute.h"

Attribute::Attribute(const std::string& name, const std::string& value)
  : m_name(name), m_value(value)
{
}

std::string Attribute::GetName() const
{
  return m_name;
}

std::string GetValue() const
{
  return m_value;
}

