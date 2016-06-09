#ifndef SLIGHTLISP_PARSER_HPP
#define SLIGHTLISP_PARSER_HPP

#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

#include <slightlisp/syntax_exception.hpp>
#include <slightlisp/value.hpp>

namespace slightlisp
{
using string = std::string;

string replace_all(const string& input, const string& from, const string& to)
{
  string spaced{input};
  if (input.empty()) return spaced;

  size_t pos = 0;
  while ((pos = spaced.find(from, pos)) != std::string::npos) {
    spaced.replace(pos, from.length(), to);
    pos += to.length();
  }

  return spaced;
}

std::vector<string> tokenize(const string& raw)
{
  string spaced = replace_all(replace_all(raw, "(", " ( "), ")", " ) ");
  std::istringstream buffer{spaced};
  std::vector<string> tokens{std::istream_iterator<string>(buffer),
                             std::istream_iterator<string>()};
  return tokens;
}

namespace detail
{
inline bool is_zero_value(string token)
{
  if (token.size() == 1) {
    return token.substr(0, 1) == "0";
  } else if (token.size() == 3) {
    return token.substr(0, 3) == "0.0";
  } else {
    return false;
  }
}

ValuePtr parse_token(string token)
{
  Numeric n = std::atof(token.c_str());
  if (n == 0) {
    // determine if the value actually was zero
    // or was just unable to be parsed
    if (is_zero_value(token)) {
      return std::move(std::make_unique<Value>(n));
    } else {
      return std::move(std::make_unique<Value>(token));
    }
  }
  return std::move(std::make_unique<Value>(n));
}

ValuePtr parse(std::vector<string>& tokens)
{
  string token = tokens[tokens.size() - 1];
  tokens.pop_back();

  // parse list
  if (token == "(") {
    ValuePtr list = std::make_unique<Value>();
    while (tokens[tokens.size() - 1] != ")") {
      list->list.push_back(parse(tokens));
    }
    tokens.pop_back();  // pop ')'
    return std::move(list);
  }
  // bad parse
  else if (token == ")") {
    throw syntax_exception{syntax_exception::UNEXPECTED_PARENS};
  }
  // parse atomic
  else {
    return std::move(parse_token(token));
  }
}

}  // detail

ValuePtr parse(std::vector<string>& tokens)
{
  if (tokens.size() == 0) {
    throw syntax_exception{syntax_exception::EMPTY_EXPRESSION};
  }
  std::reverse(tokens.begin(), tokens.end());
  return detail::parse(tokens);
}

}  // slightlisp

#endif  // SLIGHTLISP_PARSER_HPP
