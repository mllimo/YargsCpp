#include <YargsCpp/Alias.h>

namespace argc {

Alias::Alias(const std::string& init_name) { names_.insert(init_name); }

Alias::Alias(const std::forward_list<std::string> names) {
  names_.insert(names.begin(), names.end());
}

Alias::Alias(const Alias& alias) { names_ = alias.names_; }

void Alias::Add(const std::string& name) { names_.insert(name); }

void Alias::Add(const Alias& names) {
  names_.insert(names.names_.begin(), names.names_.end());
}

bool operator<(const Alias& rhs, const Alias& lhs) { 
  for (auto& name : rhs.names_) {
    if (lhs.names_.find(name) != lhs.names_.end()) return false;
  }
  return rhs.names_ < lhs.names_;
}

bool operator==(const std::string& rhs, const Alias& lhs) {
  return lhs.names_.find(rhs) != lhs.names_.end();
}


}  // namespace argc