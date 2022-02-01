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
    if (array_keys_.find(cleaned) != array_keys_.end()) {
      std::vector<std::string> values;
      for (int j = i + 1; j < argv_.size(); ++j) {
        if (std::regex_search(argv_[j], std::regex("--|-"))) break;
        values.push_back(argv_[j]);
      }
      values_[cleaned] = values;
    } else if (bool_keys_.find(cleaned) != bool_keys_.end()) {
      values_[cleaned] = true; 
    } else if (HaveValue(argv_[i])) {
      values_[cleaned] = GetValue(argv_[i]); 
    }  
  }

  return *this;
}


int Yargs::operator()(const std::string& key, int t) { 
  return std::any_cast<int>(values_[key]);
}


bool Yargs::operator()(const std::string& key, bool t) {
  if (values_.find(key) == values_.end()) return false;
  return std::any_cast<bool>(values_[key]);
}


double Yargs::operator()(const std::string& key, double t) {
  return std::any_cast<double>(values_[key]);
}


std::string Yargs::operator()(const std::string& key,
                              const std::string& t) {
  return std::any_cast<std::string>(values_[key]);
}


std::vector<std::string> Yargs::operator()(const std::string& key,
                                           const std::vector<std::string>& t) {
  return std::any_cast<std::vector<std::string>>(values_[key]);
}


Yargs& Yargs::Array(const std::string& key) { 
  array_keys_.insert(key);
  return *this;
}


Yargs& Yargs::Boolean(const std::string& key) { 
  bool_keys_.insert(key);
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

}  // namespace argc