#include <YargsCpp/Alias.h>

Alias::Alias(const std::string& init_name) { names_.insert(init_name); }

Alias::Alias(const std::forward_list<std::string> names) { names_.insert(names.begin(), names.end()); }

void Alias::Add(const std::string& name) { names_.insert(name); }

bool operator<(const Alias& rhs, const Alias& lhs) { 
  return rhs.names_ < lhs.names_;
}

bool operator==(const std::string& rhs, const Alias& lhs) {
  return lhs.names_.find(rhs) != lhs.names_.end();
}
