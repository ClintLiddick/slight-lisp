#ifndef SLIGHTLISP_EVAL_HPP
#define SLIGHTLISP_EVAL_HPP

#include <utility>

#include <slightlisp/env.hpp>
#include <slightlisp/syntax_exception.hpp>
#include <slightlisp/value.hpp>

namespace slightlisp
{
// NOTE: the List parameter doesn't refer to LISP syntactical list
// but is rather a way to pass an unknown number of Value types to
// the calling function
ValuePtr eval_fn(const EnvPtr env, const Symbol &name, List &&args)
{
  auto fn = env->find(name);
  if (fn != env->end()) {
    return fn->second(std::forward<List>(args));
  } else {
    throw syntax_exception{syntax_exception::UNKNOWN_FUNCTION};
  }
}

ValuePtr eval(const ValuePtr expr, EnvPtr env)
{
  if (!expr) {
    throw std::invalid_argument{"null expression"};
  }

  switch (expr->tag) {
    case Value::SYMBOL:
      return std::move(std::make_unique<Value>(expr->symbol));
    case Value::NUMERIC:
      return std::move(std::make_unique<Value>(expr->num));
  }
}
}

#endif  // SLIGHTLISP_EVAL_HPP
