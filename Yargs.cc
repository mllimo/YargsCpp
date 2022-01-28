#include <YargsCpp/Yargs.h>

namespace argc {

Yargs::Yargs(int argc, char* argv[]) {
  std::any value;
  std::string cleaned;
  for (size_t i = 0; i < argc; ++i) { 
    cleaned = Clean(argv[i]);
    if (HaveValue(argv[i])) {
      value = GetValue(argv[i]);
    }
    argv_[cleaned] = value;
  }
}

int Yargs::operator()(const std::string& argument, int t) { 
  return std::any_cast<int>(argv_[argument]);
}

bool Yargs::operator()(const std::string& argument, bool t) {
  return std::any_cast<bool>(argv_[argument]);
}

double Yargs::operator()(const std::string& argument, double t) {
  return std::any_cast<double>(argv_[argument]);
}

std::string Yargs::operator()(const std::string& argument,
                              const std::string& t) {
  return std::any_cast<std::string>(argv_[argument]);
}

std::string Yargs::Clean(const std::string& argument) {
  auto string = std::regex_replace(argument, std::regex("--"), "");
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