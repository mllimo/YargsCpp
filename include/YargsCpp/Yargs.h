#pragma once

#include <sstream>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <regex>
#include <map>
#include <set>
#include <any>

#include <YargsCpp/Alias.h>

#define Int int()
#define Double double()
#define Bool bool()
#define String std::string()
#define ArrayString std::vector<std::string>()

// argc from my full name: Antonio Raúl Guijarro Contreras
namespace argc {

enum Type {INT, DOUBLE, BOOL, STRING, VOID};

class Yargs {
 public:

  Yargs();

  /**
      @brief Yargs object constructor
      @param argc Number of arguments
      @param argv Arguments value
  **/
  Yargs(int argc, char** argv);


  Yargs& Parse();

  Yargs& Parse(int argc, char** argv);

  /**
      @brief  Return the value as a int
      @param  key 
      @param  t Type  
      @retval Value
  **/
  int operator()(const std::string& key, int t);

   /**
      @brief  Return the value as a bool
      @param  key 
      @param  t Type  
      @retval Value
  **/
  bool operator()(const std::string& key, bool t);

  /**
      @brief  Return the value as a double
      @param  key
      @param  t Type
      @retval Value 
  **/
  double operator()(const std::string& key, double t);

  /**
      @brief  Return the value as a std::string
      @param  key
      @param  t Type
      @retval Value
  **/
  std::string operator()(const std::string& key, const std::string& t);

  /**
      @brief  Return the value as a std::vector<string>
      @param  key 
      @param  t Type
      @retval Value
  **/
  std::vector<std::string> operator()(const std::string& key, const std::vector<std::string>& t);

  /**
      @brief  Tell the parser to interpret key as an array
      @param  key 
      @retval Reference to the class to concatenate function calls
  **/
  Yargs& Array(const std::string& key);
  
  /**
      @brief  Tell the parser to interpret key as an array
      @param  key 
      @retval Reference to the class to concatenate function calls    
  **/
  Yargs& Boolean(const std::string& key);

  Yargs& Alias(const std::string& key, const argc::Alias& alias);


 private:
  std::vector<std::string> ParseArgv(int argc, char** argv);
  std::string Clean(const std::string& argument);
  bool HaveValue(const std::string& argument);
  std::any GetValue(const std::string& argument);

  std::vector<std::string> argv_;
  std::set<argc::Alias> bool_keys_;
  std::set<argc::Alias> array_keys_;
  std::map<argc::Alias, std::any> values_;
};
}
