#ifndef SLIGHTLISP_TYPES_HPP
#define SLIGHTLISP_TYPES_HPP

#include <algorithm>
#include <exception>
#include <memory>
#include <string>
#include <vector>

#include <iostream>

namespace slightlisp
{
struct Type {
  enum TYPE { NUMERIC, SYMBOL, LIST } tag;
  double num;
  std::string symbol;
  std::vector<std::unique_ptr<Type>> list;

  // default construct creates a list type
  Type()
      : tag{LIST}
      , num{}
      , symbol{}
      , list{}
  {
  }

  explicit Type(double num)
      : tag{NUMERIC}
      , num{num}
      , symbol{}
      , list{}
  {
  }

  explicit Type(std::string symbol)
      : tag{SYMBOL}
      , num{}
      , symbol{symbol}
      , list{}
  {
  }

  explicit Type(std::vector<std::unique_ptr<Type>> &&other_list)
      : tag{LIST}
      , num{}
      , symbol{}
      , list{std::move(other_list)}
  {
  }

  // non-copyable
  Type(const Type &other) = delete;
  Type &operator=(const Type &other) = delete;

  // movable
  Type(Type &&other)
      : tag{other.tag}
      , num{other.num}
      , symbol{other.symbol}
      , list{std::move(other.list)}
  {
  }

  Type &operator=(Type &&other)
  {
    tag = other.tag;
    num = other.num;
    symbol = other.symbol;
    list = std::move(other.list);
    return *this;
  }

  bool operator==(const Type &other) const
  {
    if (tag == other.tag) {
      switch (tag) {
        case NUMERIC:
          return num == other.num;
        case SYMBOL:
          return symbol == other.symbol;
        case LIST:
          if (list.size() != other.list.size()) {
            return false;
          } else {
            for (int i = 0; i < list.size(); ++i) {
              if (*list[i] != *other.list[i]) {
                return false;
              }
            }
            return true;
          }
      }
    } else {
      return false;
    }
  }

  bool operator!=(const Type &other) const { return !(*this == other); }

  friend std::ostream &operator<<(std::ostream &os, const Type &type);
};

std::ostream &operator<<(::std::ostream &os, const Type &type)
{
  switch (type.tag) {
    case Type::NUMERIC:
      os << type.num;
    case Type::SYMBOL:
      os << type.symbol;
    case Type::LIST:
      os << "[ ";
      for (auto &t : type.list) {
        os << *t << " ";
      }
      os << "]";
  }
  return os;
}

// using List = std::vector<std::unique_ptr<Type>>;
using TypePtr = std::unique_ptr<Type>;
using Symbol = std::string;
using Numeric = double;

class syntax_exception : public std::exception
{
public:
  enum type { UNEXPECTED_PARENS, MISSING_PARENS, EMPTY_EXPRESSION } tag;

  explicit syntax_exception(type tag)
      : tag{tag}
  {
  }

  virtual const char *what() const noexcept
  {
    switch (tag) {
      case UNEXPECTED_PARENS:
        return "UNEXPECTED_PARENS";
      case MISSING_PARENS:
        return "MISSING_PARENS";
      case EMPTY_EXPRESSION:
        return "EMPTY_EXPRESSION";
    }
  }
};

}  // ns

#endif  // SLIGHTLISP_TYPES_HPP
