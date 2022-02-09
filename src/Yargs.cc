#include <YargsCpp/Yargs.h>

namespace argc {

Yargs::Yargs() {}


Yargs::Yargs(int argc, char* argv[]) { argv_ = ParseArgv(argc, argv); }


Yargs& Yargs::Parse(int argc, char* argv[]) {
  argv_ = ParseArgv(argc, argv);
  return Parse();
}

// Refac
Yargs& Yargs::Parse() {
  std::any value;
  std::string cleaned;

  for (size_t i = 0; i < argv_.size(); ++i) {
    cleaned = Clean(argv_[i]);
    argc::Alias alias(GetAllAlias(cleaned));
    if (array_keys_.find(alias) != array_keys_.end()) {
      std::vector<std::string> values;
      for (size_t j = i + 1; j < argv_.size(); ++j) {
        if (std::regex_search(argv_[j], std::regex("--|-"))) break;
        values.push_back(argv_[j]);
      }
      values_[alias] = values;
    } else if (bool_keys_.find(alias) != bool_keys_.end()) {
      values_[alias] = true; 
    } else if (HaveValue(argv_[i])) {
      values_[alias] = GetValue(argv_[i]); 
    }  
  }

  return *this;
}


int Yargs::operator()(const std::string& key, int t) {
  argc::Alias alias(GetAllAlias(key));
  return std::any_cast<int>(values_[alias]);
}


bool Yargs::operator()(const std::string& key, bool t) {
  argc::Alias alias(GetAllAlias(key));
  if (values_.find(alias) == values_.end()) return false;
  return std::any_cast<bool>(values_[key]);
}


double Yargs::operator()(const std::string& key, double t) {
  argc::Alias alias(GetAllAlias(key));
  return std::any_cast<double>(values_[alias]);
}


std::string Yargs::operator()(const std::string& key,
                              const std::string& t) {
  argc::Alias alias(GetAllAlias(key));
  return std::any_cast<std::string>(values_[alias]);
}


std::vector<std::string> Yargs::operator()(const std::string& key,
                                           const std::vector<std::string>& t) {
  argc::Alias alias(GetAllAlias(key));
  return std::any_cast<std::vector<std::string>>(values_[alias]);
}


Yargs& Yargs::Array(const std::string& key) {
  array_keys_.insert(key);
  return *this;
}


Yargs& Yargs::Boolean(const std::string& key) { 
  bool_keys_.insert(key);
  return *this;
}

// Optimizar
Yargs& Yargs::Alias(const std::string& key, const argc::Alias& alias) {
  auto it = std::find(alias_.begin(), alias_.end(), key);
  if (it != alias_.end()) {
    it->Add(alias);
  } else {
    argc::Alias to_add(key);
    to_add.Add(alias);
    alias_.push_back(to_add);
  }

  return *this;
}


std::vector<std::string> Yargs::ParseArgv(int argc, char** argv) {
  std::vector<std::string> arguments;
  arguments.insert(arguments.end(), argv, argv + argc);
  return arguments;
}


std::string Yargs::Clean(const std::string& argument) {
  auto string = std::regex_replace(argument, std::regex("--|-"), "");
  return std::regex_replace(string, std::regex("=.*$"), "");
}


bool Yargs::HaveValue(const std::string& argument) {
  for (char c : argument) {
    if (c == '=') return true;
  }
  return false;
}


std::any Yargs::GetValue(const std::string& argument) {
  std::string value_str;
  std::any value;
  bool has_dot = false;
  Type type = Type::VOID;

  for (auto rit = argument.rbegin(); rit != argument.rend(); ++rit) {
    if (*rit == '=') break;
    if (*rit == '.') has_dot = true;

    if (isdigit(*rit) && !has_dot && type != Type::STRING) type = Type::INT;
    if (isdigit(*rit) && has_dot && type != Type::STRING) type = Type::DOUBLE;
    if (isalpha(*rit)) type = Type::STRING;

    value_str.push_back(*rit);
  }

  std::reverse(value_str.begin(), value_str.end());
  if (value_str == "true" || value_str == "false") type = Type::BOOL;

  switch (type) {
    case argc::INT:
      value = std::stoi(value_str);
      break;
    case argc::DOUBLE:
      value = std::stod(value_str);
      break;
    case argc::BOOL:
      value = value_str == "true";
      break;
    case argc::STRING:
      value = value_str;
      break;
  }

  return value;
}

argc::Alias Yargs::GetAllAlias(const argc::Alias& alias) { 
  auto it = std::find(alias_.begin(), alias_.end(), alias);
  if (it != alias_.end()) return *it;
  return alias;
}


}  // namespace argc