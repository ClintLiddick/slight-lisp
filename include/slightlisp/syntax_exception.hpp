#ifndef SLIGHTLISP_SYNTAX_EXCEPTION_HPP
#define SLIGHTLISP_SYNTAX_EXCEPTION_HPP

#include <exception>
#include <string>

namespace slightlisp
{
class syntax_exception : public std::exception
{
public:
  enum TYPE {
    UNEXPECTED_PARENS,
    MISSING_PARENS,
    EMPTY_EXPRESSION,
    UNKNOWN_FUNCTION,
    INVALID_IF_EXPRESSION
  } tag;

  std::string description;

  syntax_exception(TYPE tag, std::string details = "")
      : tag{tag}
  {
    switch (tag) {
      case UNEXPECTED_PARENS:
        description = "UNEXPECTED_PARENS " + details;
        break;
      case MISSING_PARENS:
        description = "MISSING_PARENS " + details;
        break;
      case EMPTY_EXPRESSION:
        description = "EMPTY_EXPRESSION " + details;
        break;
      case UNKNOWN_FUNCTION:
        description = "UNKNOWN_FUNCTION " + details;
        break;
      case INVALID_IF_EXPRESSION:
        description = "INVALID_IF_EXPRESSION " + details;
        break;
    }
  }

  virtual const char *what() const noexcept
  {
    return description.c_str();
  }
};

}  // ns

#endif  // SLIGHTLISP_SYNTAX_EXCEPTION_HPP
