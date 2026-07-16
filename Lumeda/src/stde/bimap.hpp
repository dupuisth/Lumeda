#pragma once

#include <initializer_list>
#include <map>
#include <stdexcept>
#include <utility>

namespace stde
{
template <typename Key, typename Value>
class bimap
{
public:
  using key_type = Key;
  using value_type = Value;

  bimap() = default;

  bimap(std::initializer_list<std::pair<Key, Value>> entries)
  {
    for (const auto& [key, value] : entries)
    {
      if (!insert(key, value))
        throw std::invalid_argument("Duplicate bimap key or value");
    }
  }

  bool insert(const Key& key, const Value& value)
  {
    // A bimap requires both sides to be unique.
    if (m_Forward.find(key) != m_Forward.end() || m_Reverse.find(value) != m_Reverse.end())
    {
      return false;
    }

    m_Forward.emplace(key, value);

    try
    {
      m_Reverse.emplace(value, key);
    }
    catch (...)
    {
      // Keep both maps synchronized if allocation throws.
      m_Forward.erase(key);
      throw;
    }

    return true;
  }

  bool has_key(const Key& key) const { return m_Forward.find(key) != m_Forward.end(); }

  bool has_value(const Value& value) const { return m_Reverse.find(value) != m_Reverse.end(); }

  const Value& get_value(const Key& key) const { return m_Forward.at(key); }

  const Key& get_key(const Value& value) const { return m_Reverse.at(value); }

  std::size_t size() const { return m_Forward.size(); }

private:
  std::map<Key, Value> m_Forward;
  std::map<Value, Key> m_Reverse;
};
} // namespace stde