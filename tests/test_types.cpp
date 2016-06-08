#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <slightlisp/types.hpp>

using namespace slightlisp;

/***************************************************************************/

TEST(TypeTests, ListDefaultConstruction)
{
  Type t;
  ASSERT_EQ(Type::LIST, t.tag);
}

TEST(TypeTests, SymbolConstruction)
{
  Type t{"str"};
  ASSERT_EQ(Type::SYMBOL, t.tag);
}

TEST(TypeTests, NumericEquality)
{
  Type t1{1.0}, t2{1.0};
  ASSERT_EQ(t1, t2);
}

TEST(TypeTests, SymbolEquality)
{
  Type t1{"test"}, t2{"test"};
  ASSERT_EQ(t1, t2);
}

TEST(TypeTests, ListEquality)
{
  Type t1, t2;
  t1.list.push_back(std::make_unique<Type>("t1"));
  t1.list.push_back(std::make_unique<Type>("t2"));
  t2.list.push_back(std::make_unique<Type>("t1"));
  t2.list.push_back(std::make_unique<Type>("t2"));
  ASSERT_EQ(t1, t2);
}

TEST(TypeTests, NumericToString)
{
  Type t{1};
  ASSERT_EQ(t.to_string(), "1");
}

TEST(TypeTests, SymbolToString)
{
  Type t{"a"};
  ASSERT_EQ(t.to_string(), "a");
}

TEST(TypeTests, EmptyListToString)
{
  Type t;
  ASSERT_EQ(t.to_string(), "()");
}

TEST(TypeTests, SingleItemString)
{
  Type t;
  t.list.push_back(std::make_unique<Type>(1));
  ASSERT_EQ(t.to_string(), "(1)");
}

TEST(TypeTests, MultiItemString)
{
  Type t;
  t.list.push_back(std::make_unique<Type>(1));
  t.list.push_back(std::make_unique<Type>(2));
  t.list.push_back(std::make_unique<Type>(3));
  ASSERT_EQ(t.to_string(), "(1 2 3)");
}
