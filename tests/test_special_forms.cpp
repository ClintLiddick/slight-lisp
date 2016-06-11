#include <slightlisp/special_forms.hpp>
#include <stdexcept>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace slightlisp;

using std::make_unique;

TEST(AddTests, Valid)
{
  List list;
  list.push_back(make_unique<Value>(1));
  list.push_back(make_unique<Value>(2));
  ValuePtr v = make_unique<Value>(3);
  ASSERT_EQ(*add(std::move(list)), *v);
}

TEST(AddTests, NotEnoughArgs)
{
  List list;
  list.push_back(make_unique<Value>(1));
  ASSERT_THROW(add(std::move(list)), std::invalid_argument);
}

TEST(AddTests, TooManyArgs)
{
  List list;
  list.push_back(make_unique<Value>(1));
  list.push_back(make_unique<Value>(1));
  list.push_back(make_unique<Value>(1));
  ASSERT_THROW(add(std::move(list)), std::invalid_argument);
}

TEST(AddTests, NonNumericArg)
{
  List list;
  list.push_back(make_unique<Value>(1));
  list.push_back(make_unique<Value>(""));
  ASSERT_THROW(add(std::move(list)), std::invalid_argument);
}

TEST(GreaterThanTests, True)
{
  List list;
  list.push_back(make_unique<Value>(2));
  list.push_back(make_unique<Value>(1));
  Value true_val{true, Value::BOOL};
  ASSERT_EQ(*gt(std::move(list)), true_val);
}

TEST(GreaterThanTests, False)
{
  List list;
  list.push_back(make_unique<Value>(1));
  list.push_back(make_unique<Value>(2));
  Value false_val{false, Value::BOOL};
  ASSERT_EQ(*gt(std::move(list)), false_val);
}
