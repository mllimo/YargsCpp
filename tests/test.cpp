#include "gtest/gtest.h"
#include <YargsCpp/Yargs.h>

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(YargsCpp, ParameterConstructor) {
  int argc = 3;
  char* argv[] = {"mi.exe", "--ships=3", "--pirates=10"};
  argc::Yargs yargs(argc, argv);
  yargs.Parse();
  EXPECT_EQ(yargs("ships", Int), 3);
  EXPECT_EQ(yargs("pirates", Int), 10);
}