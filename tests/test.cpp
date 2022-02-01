#include "gtest/gtest.h"
#include <string>
#include <vector>

#include <YargsCpp/Yargs.h>

TEST(YargsCpp, ParameterConstructor) {
  int argc = 3;
  char* argv[] = {"mi.exe", "--ships=3", "--pirates=10"};
  argc::Yargs yargs(argc, argv);
}

TEST(YargsCpp, ParseDefault) {
  int argc = 3;
  char* argv[] = {"mi.exe", "--ships=3", "--pirates=10"};
  argc::Yargs yargs(argc, argv);
  yargs.Parse();
  EXPECT_EQ(yargs("ships", Int), 3);
  EXPECT_EQ(yargs("pirates", Int), 10);
}

TEST(YargsCpp, ParseParameters) {
  int argc = 3;
  char* argv[] = {"mi.exe", "--ships=3", "--pirates=10"};
  argc::Yargs yargs;
  yargs.Parse(argc, argv);
  EXPECT_EQ(yargs("ships", Int), 3);
  EXPECT_EQ(yargs("pirates", Int), 10);
}

TEST(YargsCpp, ArrayArguments) {
  int argc = 4;
  char* argv[] = {"mi.exe", "--names", "Antonio", "Raul"};
  std::vector<std::string> v_names = {"Antonio", "Raul"};
  argc::Yargs yargs(argc, argv);
  yargs.Array("names").Parse();
  auto names = yargs("names", ArrayString);
  for (size_t i = 0; i < names.size(); ++i) {
    EXPECT_EQ(names[i], v_names[i]);
  }
}

TEST(YargsCpp, ArgumentsMixed) {
  int argc = 5;
  char* argv[] = {"mi.exe", "--names", "Antonio", "Raul", "--age=22"};
  std::vector<std::string> v_names = {"Antonio", "Raul"};
  argc::Yargs yargs(argc, argv);
  yargs.Array("names").Parse();
  auto names = yargs("names", ArrayString);
  for (size_t i = 0; i < names.size(); ++i) {
    EXPECT_EQ(names[i], v_names[i]);
  }
  EXPECT_EQ(yargs("age", Int), 22);
}