#include <slightlisp/eval.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace slightlisp;

class EvalTests : public ::testing::Test
{
public:
  EnvPtr env;
  EvalTests()
      : env{std::make_shared<Env>(global_env())}
  {
  }
};

TEST_F(EvalTests, Add)
{
  List args;
  args.push_back(std::make_unique<Value>(1));
  args.push_back(std::make_unique<Value>(2));
  ASSERT_EQ(*eval_fn(env, "+", std::move(args)), Value{3});
}

TEST_F(EvalTests, UnknownFunction)
{
  List args;
  ASSERT_THROW(eval_fn(env, "this_will_never_be_a_fn_name", std::move(args)),
               syntax_exception);
}

TEST_F(EvalTests, NullExpr)
{
  ASSERT_THROW(eval(nullptr, env), std::invalid_argument);
}

TEST_F(EvalTests, ReturnSymbol)
{
  ValuePtr expr = std::make_unique<Value>("a");
  Symbol s{"a"};
  ASSERT_EQ(eval(std::move(expr), env)->symbol, s);
}

TEST_F(EvalTests, ReturnNumeric)
{
  ValuePtr expr = std::make_unique<Value>(1);
  Numeric n{1};
  ASSERT_EQ(eval(std::move(expr), env)->num, n);
}
