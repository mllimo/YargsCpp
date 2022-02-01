#pragma once

#include <set>
#include <string>
#include <forward_list>

class Alias {
  public:
   Alias(const std::string& init_name);
   Alias(const std::forward_list<std::string> names);

   void Add(const std::string& name);

  friend bool operator<(const Alias& rhs, const Alias& lhs);
  friend bool operator==(const std::string& rhs, const Alias& lhs);

  private:
  std::set<std::string> names_;
};
