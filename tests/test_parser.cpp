#include <slightlisp/parser.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace slightlisp;

using string = std::string;
using ::testing::ContainerEq;

/***************************************************************************/

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

TEST(ParseTests, Empty)
{
  auto tokens = tokenize("");
  ASSERT_THROW(parse(tokens), syntax_exception);
}

TEST(ParseTests, NoParens)
{
  auto tokens = tokenize("1");
  ValuePtr parsed = parse(tokens);
  ValuePtr one = std::make_unique<Value>(1);
  ASSERT_EQ(*parsed, *one);
}

TEST(ParseTests, EmptyList)
{
  auto tokens = tokenize("()");
  ValuePtr parsed = parse(tokens);
  Value list;
  ASSERT_EQ(*parsed, list);
}

TEST(ParseTests, ListOfIntNumerics)
{
  auto tokens = tokenize("(1 2 3)");
  Value list;
  list.list.push_back(std::make_unique<Value>(1));
  list.list.push_back(std::make_unique<Value>(2));
  list.list.push_back(std::make_unique<Value>(3));
  ValuePtr parsed = parse(tokens);
  ASSERT_EQ(*parsed, list);
}

TEST(ParseTests, ListOfFloatNumerics)
{
  auto tokens = tokenize("(1.0 2.0 3.0)");
  Value list;
  list.list.push_back(std::make_unique<Value>(1.0));
  list.list.push_back(std::make_unique<Value>(2.0));
  list.list.push_back(std::make_unique<Value>(3.0));
  ValuePtr parsed = parse(tokens);
  ASSERT_EQ(*parsed, list);
}

TEST(ParseTests, Zero)
{
  auto tokens = tokenize("0.0");
  Value zero{0};
  ValuePtr parsed = parse(tokens);
  ASSERT_EQ(*parsed, zero);
}

TEST(ParseTests, DISABLED_LongZeroString)
{
  auto tokens = tokenize("00");
  Value zero{0};
  ValuePtr parsed = parse(tokens);
  ASSERT_EQ(*parsed, zero) << "This is a documented deficiency in the parser";
}

TEST(ParseTests, ListOfSymbols)
{
  auto tokens = tokenize("(first second third)");
  Value list;
  list.list.push_back(std::make_unique<Value>("first"));
  list.list.push_back(std::make_unique<Value>("second"));
  list.list.push_back(std::make_unique<Value>("third"));
  ValuePtr parsed = parse(tokens);
  ASSERT_EQ(*parsed, list);
}

TEST(ParseTests, NestedLists)
{
  auto tokens = tokenize("(first (second))");
  Value outer_list, inner_list;
  outer_list.list.push_back(std::make_unique<Value>("first"));
  inner_list.list.push_back(std::make_unique<Value>("second"));
  outer_list.list.push_back(std::make_unique<Value>(std::move(inner_list)));
  ValuePtr parsed = parse(tokens);
  ASSERT_EQ(*parsed, outer_list);
}
