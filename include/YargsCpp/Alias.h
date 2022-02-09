#pragma once

#include <set>
#include <string>
#include <forward_list>

namespace argc {

class Alias {
 public:
  Alias(const std::string& init_name);
  Alias(const std::forward_list<std::string> names);
  Alias(const Alias& alias);

  void Add(const std::string& name);
  void Add(const Alias& name);

  friend bool operator<(const Alias& rhs, const Alias& lhs);
  friend bool operator==(const Alias& rhs, const Alias& lhs);
  friend bool operator==(const std::string& rhs, const Alias& lhs);

 private:
  std::set<std::string> names_;
};

}  // namespace argc
