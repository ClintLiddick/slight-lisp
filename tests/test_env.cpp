#include <slightlisp/env.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace slightlisp;

TEST(EnvTests, AllSpecialForms)
{
  Env env = global_env();
  EXPECT_NO_THROW(env.at("+"));
}
  
  
