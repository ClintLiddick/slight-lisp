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
  ASSERT_EQ(*addValues(std::move(list)), *v);
}

TEST(AddTests, NotEnoughArgs)
{
  List list;
  list.push_back(make_unique<Value>(1));
  ASSERT_THROW(addValues(std::move(list)), std::invalid_argument);
}

TEST(AddTests, TooManyArgs)
{
  List list;
  list.push_back(make_unique<Value>(1));
  list.push_back(make_unique<Value>(1));
  list.push_back(make_unique<Value>(1));
  ASSERT_THROW(addValues(std::move(list)), std::invalid_argument);
}

TEST(AddTests, NonNumericArg)
{
  List list;
  list.push_back(make_unique<Value>(1));
  list.push_back(make_unique<Value>(""));
  ASSERT_THROW(addValues(std::move(list)), std::invalid_argument);
}
