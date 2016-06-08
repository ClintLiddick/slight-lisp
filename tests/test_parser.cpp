#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <stack>
#include <slightlisp/parser.hpp>
#include <slightlisp/types.hpp>

using namespace slightlisp;

using string = std::string;
using ::testing::ContainerEq;

TEST(ReplaceAllTests, SingleChar)
{
  string start = "abc";
  ASSERT_EQ(replace_all(start, "b", "z"), "azc");
}

TEST(ReplaceAllTests, ShorterWithLonger)
{
  string start = "abc";
  ASSERT_EQ(replace_all(start, "b", "1234"), "a1234c");
}

TEST(ReplaceAllTests, LongerWithShorter)
{
  string start = "abc";
  ASSERT_EQ(replace_all(start, "ab", "z"), "zc");
}

TEST(ReplaceAllTests, ReplaceMultiple)
{
  string start = "abcabc";
  ASSERT_EQ(replace_all(start, "a", "z"), "zbczbc");
}

TEST(ReplaceAllTests, ReplaceConsecutive)
{
  string start = "aa";
  ASSERT_EQ(replace_all(start, "a", "z"), "zz");
}

TEST(ReplaceAllTests, ReplaceWithSpace)
{
  string start = "abcabc";
  ASSERT_EQ(replace_all(start, "a", " "), " bc bc");
}

TEST(ReplaceAllTests, ReplaceWithSimilar)
{
  string start = "abcabc";
  ASSERT_EQ(replace_all(start, "a", " a"), " abc abc");
}

TEST(ReplaceAllTests, EmptyFromString)
{
  ASSERT_EQ(replace_all("", "a", "1"), "");
}

TEST(ReplaceAllTests, NestedCalls)
{
  ASSERT_EQ(replace_all(replace_all("abc", "a", "1"), "b", "2"), "12c");
}

/***************************************************************************/

TEST(TokenizeTests, OneToken)
{
  std::vector<std::string> tokens;
  tokens.push_back("blah");
  ASSERT_THAT(tokenize("blah"), ContainerEq(tokens));
}

TEST(TokenizeTests, TwoTokens)
{
  std::vector<std::string> tokens;
  tokens.push_back("+");
  tokens.push_back("-");
  ASSERT_THAT(tokenize("+ -"), ContainerEq(tokens));
}

TEST(TokenizeTests, EmptyParens)
{
  std::vector<std::string> tokens;
  tokens.push_back("(");
  tokens.push_back(")");
  ASSERT_THAT(tokenize("()"), ContainerEq(tokens));
}

TEST(TokenizeTests, UnspacedList)
{
  std::vector<std::string> tokens;
  tokens.push_back("(");
  tokens.push_back("a");
  tokens.push_back(")");
  ASSERT_THAT(tokenize("(a)"), ContainerEq(tokens));
}

TEST(TokenizeTests, SpacedList)
{
  std::vector<std::string> tokens;
  tokens.push_back("(");
  tokens.push_back("a");
  tokens.push_back(")");
  ASSERT_THAT(tokenize("( a )"), ContainerEq(tokens));
}

TEST(TokenizeTests, FloatingPointTokens)
{
  std::vector<std::string> tokens;
  tokens.push_back("1.0");
  tokens.push_back("1.5");
  ASSERT_THAT(tokenize("1.0 1.5"), ContainerEq(tokens));
}

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


/***************************************************************************/

TEST(ParseTests, Empty)
{
  auto tokens = tokenize("");
  ASSERT_THROW(parse(tokens), syntax_exception);
}

TEST(ParseTests, NoParens)
{
  auto tokens = tokenize("1");
  TypePtr parsed = parse(tokens);
  TypePtr one = std::make_unique<Type>(1);
  ASSERT_EQ(*parsed, *one);
}

TEST(ParseTests, EmptyList)
{
  auto tokens = tokenize("()");
  TypePtr parsed = parse(tokens);
  Type list;
  ASSERT_EQ(*parsed, list);
}

TEST(ParseTests, ListOfIntNumerics)
{
  auto tokens = tokenize("(1 2 3)");
  Type list;
  list.list.push_back(std::make_unique<Type>(1));
  list.list.push_back(std::make_unique<Type>(2));
  list.list.push_back(std::make_unique<Type>(3));
  TypePtr parsed = parse(tokens);
  ASSERT_EQ(*parsed, list);
}

TEST(ParseTests, ListOfFloatNumerics)
{
  auto tokens = tokenize("(1.0 2.0 3.0)");
  Type list;
  list.list.push_back(std::make_unique<Type>(1.0));
  list.list.push_back(std::make_unique<Type>(2.0));
  list.list.push_back(std::make_unique<Type>(3.0));
  TypePtr parsed = parse(tokens);
  ASSERT_EQ(*parsed, list);
}

TEST(ParseTests, Zero)
{
  auto tokens = tokenize("0.0");
  Type zero{0};
  TypePtr parsed = parse(tokens);
  ASSERT_EQ(*parsed, zero);
}

TEST(ParseTests, DISABLED_LongZeroString)
{
  auto tokens = tokenize("00");
  Type zero{0};
  TypePtr parsed = parse(tokens);
  ASSERT_EQ(*parsed, zero) << "This is a documented deficiency in the parser";
}

TEST(ParseTests, ListOfSymbols)
{
  auto tokens = tokenize("(first second third)");
  Type list;
  list.list.push_back(std::make_unique<Type>("first"));
  list.list.push_back(std::make_unique<Type>("second"));
  list.list.push_back(std::make_unique<Type>("third"));
  TypePtr parsed = parse(tokens);
  ASSERT_EQ(*parsed, list);
}

TEST(ParseTests, NestedLists)
{
  auto tokens = tokenize("(first (second))");
  Type outer_list, inner_list;
  outer_list.list.push_back(std::make_unique<Type>("first"));
  inner_list.list.push_back(std::make_unique<Type>("second"));
  outer_list.list.push_back(std::make_unique<Type>(std::move(inner_list)));
  TypePtr parsed = parse(tokens);
  ASSERT_EQ(*parsed, outer_list);
}

