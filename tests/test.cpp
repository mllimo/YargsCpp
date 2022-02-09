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

TEST(YargsCpp, BoolArguments) {
  int argc = 2;
  char* argv[] = {"mi.exe", "--debug"};
  argc::Yargs yargs(argc, argv);
  yargs.Boolean("debug").Parse();
  EXPECT_TRUE(yargs("debug", Bool));
}

TEST(YargsCpp, ArgumentsMixed1) {
  int argc = 6;
  char* argv[] = {"mi.exe", "--names", "Antonio", "Raul", "--age=22", "--debug"};
  std::vector<std::string> v_names = {"Antonio", "Raul"};
  argc::Yargs yargs(argc, argv);
  yargs.Array("names").Boolean("debug").Parse();
  auto names = yargs("names", ArrayString);
  for (size_t i = 0; i < names.size(); ++i) {
    EXPECT_EQ(names[i], v_names[i]);
  }
  EXPECT_EQ(yargs("age", Int), 22);
}

TEST(YargsCpp, Alias) {
  int argc = 2;
  char* argv[] = {"mi.exe", "--debug"};
  argc::Yargs yargs(argc, argv);
  yargs.Boolean("debug").Alias("debug", {"d"}).Parse();
  EXPECT_TRUE(yargs("d", Bool));
}

