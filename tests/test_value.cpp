#include <slightlisp/value.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace slightlisp;

/***************************************************************************/

TEST(ValueTests, ListDefaultConstruction)
{
  Value t;
  ASSERT_EQ(Value::LIST, t.tag);
}

TEST(ValueTests, SymbolConstruction)
{
  Value t{"str"};
  ASSERT_EQ(Value::SYMBOL, t.tag);
}

TEST(ValueTests, NumericEquality)
{
  Value t1{1.0}, t2{1.0};
  ASSERT_EQ(t1, t2);
}

TEST(ValueTests, SymbolEquality)
{
  Value t1{"test"}, t2{"test"};
  ASSERT_EQ(t1, t2);
}

TEST(ValueTests, ListEquality)
{
  Value t1, t2;
  t1.list.push_back(std::make_unique<Value>("t1"));
  t1.list.push_back(std::make_unique<Value>("t2"));
  t2.list.push_back(std::make_unique<Value>("t1"));
  t2.list.push_back(std::make_unique<Value>("t2"));
  ASSERT_EQ(t1, t2);
}

TEST(ValueTests, NumericToString)
{
  Value t{1};
  ASSERT_EQ(t.to_string(), "1");
}

TEST(ValueTests, SymbolToString)
{
  Value t{"a"};
  ASSERT_EQ(t.to_string(), "a");
}

TEST(ValueTests, EmptyListToString)
{
  Value t;
  ASSERT_EQ(t.to_string(), "()");
}

TEST(ValueTests, SingleItemString)
{
  Value t;
  t.list.push_back(std::make_unique<Value>(1));
  ASSERT_EQ(t.to_string(), "(1)");
}

TEST(ValueTests, MultiItemString)
{
  Value t;
  t.list.push_back(std::make_unique<Value>(1));
  t.list.push_back(std::make_unique<Value>(2));
  t.list.push_back(std::make_unique<Value>(3));
  ASSERT_EQ(t.to_string(), "(1 2 3)");
}
