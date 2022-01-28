#pragma once

#include <sstream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <regex>
#include <map>
#include <any>

#define Int int()
#define Double double()
#define Bool bool()
#define String std::string()

// argc from my full name: Antonio Raúl Guijarro Contreras
namespace argc {

enum Type {INT, DOUBLE, BOOL, STRING, VOID};

class Yargs {
 public:
  Yargs(int argc, char* argv[]);

  int operator()(const std::string& argument, int t);
  bool operator()(const std::string& argument, bool t);
  double operator()(const std::string& argument, double t);
  std::string operator()(const std::string& argument, const std::string& t);


 private:
  std::string Clean(const std::string& argument);
  bool HaveValue(const std::string& argument);
  std::any GetValue(const std::string& argument);

  std::map<std::string, std::any> argv_;
};
}
