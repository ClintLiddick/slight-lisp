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

/***************************************************************************/

TEST(ValueComparisonTests, NumericEquality)
{
  Value t1{1.0}, t2{1.0};
  ASSERT_EQ(t1, t2);
}

TEST(ValueComparisonTests, SymbolEquality)
{
  Value t1{"test"}, t2{"test"};
  ASSERT_EQ(t1, t2);
}

TEST(ValueComparisonTests, ListEquality)
{
  Value t1, t2;
  t1.list.push_back(std::make_unique<Value>("t1"));
  t1.list.push_back(std::make_unique<Value>("t2"));
  t2.list.push_back(std::make_unique<Value>("t1"));
  t2.list.push_back(std::make_unique<Value>("t2"));
  ASSERT_EQ(t1, t2);
}

TEST(ValueComparisonTests, BoolEquality)
{
  Value t1{true, Value::BOOL}, t2{true, Value::BOOL};
  EXPECT_EQ(t1, t2);
  Value f1{false, Value::BOOL}, f2{false, Value::BOOL};
  EXPECT_EQ(t1, t2);
  EXPECT_NE(t1, f1);
}

TEST(ValueComparisonTests, NumericGT)
{
  Value t1{2.0}, t2{1.0};
  ASSERT_GT(t1, t2);
}

TEST(ValueComparisonTests, SymbolGT)
{
  Value t1{"z"}, t2{"a"};
  ASSERT_GT(t1, t2);
}

TEST(ValueComparisonTests, DISABLED_ListGT)
{
  // TODO
  Value t1, t2;
  t1.list.push_back(std::make_unique<Value>(2));
  t2.list.push_back(std::make_unique<Value>(1));
  ASSERT_GT(t1, t2);
}

TEST(ValueComparisonTests, BoolGT)
{
  Value t{true, Value::BOOL}, f{false, Value::BOOL};
  ASSERT_GT(t, f);
}

TEST(ValueComparisonTests, NumericLT)
{
  Value t1{1.0}, t2{2.0};
  ASSERT_LT(t1, t2);
}

TEST(ValueComparisonTests, SymbolLT)
{
  Value t1{"a"}, t2{"z"};
  ASSERT_LT(t1, t2);
}

TEST(ValueComparisonTests, DISABLED_ListLT)
{
  // TODO
  Value t1, t2;
  t1.list.push_back(std::make_unique<Value>(1));
  t2.list.push_back(std::make_unique<Value>(2));
  ASSERT_LT(t1, t2);
}

TEST(ValueComparisonTests, BoolLT)
{
  Value t{true, Value::BOOL}, f{false, Value::BOOL};
  ASSERT_LT(f, t);
}

/***************************************************************************/

TEST(ValueComparisonTests, NumericToString)
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

TEST(ValueTests, BoolToString)
{
  Value b{true, Value::BOOL};
  ASSERT_EQ(b.to_string(), "true");
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
