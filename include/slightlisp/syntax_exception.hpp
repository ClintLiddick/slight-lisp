#ifndef SLIGHTLISP_SYNTAX_EXCEPTION_HPP
#define SLIGHTLISP_SYNTAX_EXCEPTION_HPP

#include <exception>

namespace slightlisp
{
class syntax_exception : public std::exception
{
public:
  enum TYPE {
    UNEXPECTED_PARENS,
    MISSING_PARENS,
    EMPTY_EXPRESSION,
    UNKNOWN_FUNCTION
  } tag;

  explicit syntax_exception(TYPE tag)
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
      case UNKNOWN_FUNCTION:
        return "UNKNOWN_FUNCTION";
    }
  }
};

}  // ns

#endif  // SLIGHTLISP_SYNTAX_EXCEPTION_HPP
