#ifndef SLIGHTLISP_EVAL_HPP
#define SLIGHTLISP_EVAL_HPP

#include <iterator>
#include <utility>

#include <slightlisp/env.hpp>
#include <slightlisp/syntax_exception.hpp>
#include <slightlisp/value.hpp>

namespace slightlisp
{
inline ValuePtr eval_list(List &&list, EnvPtr env)
{
  ValuePtr values = std::make_unique<Value>();
  return nullptr;
}

// NOTE: the List parameter doesn't refer to LISP syntactical list
// but is rather a way to pass an unknown number of Value types to
// the calling function
inline ValuePtr eval_fn(const EnvPtr env, const Symbol &name, List &&args)
{
  auto fn = env->find(name);
  if (fn != env->end()) {
    return fn->second(std::forward<List>(args));
  } else {
    throw syntax_exception{syntax_exception::UNKNOWN_FUNCTION};
  }
}

ValuePtr eval(ValuePtr expr, EnvPtr env)
{
  if (!expr) {
    throw std::invalid_argument{"null expression"};
  }

  switch (expr->tag) {
    case Value::SYMBOL:
      // TODO if
      // TODO define
      // TODO quote
      return std::move(std::make_unique<Value>(expr->symbol));
    case Value::NUMERIC:
      return std::move(std::make_unique<Value>(expr->num));
    case Value::LIST:
      if (expr->list.size() == 0) {
        throw syntax_exception{syntax_exception::UNEXPECTED_PARENS};
      }
      ValuePtr proc = eval(std::move(expr->list[0]), env);
      if (proc->tag != Value::SYMBOL) {
        throw syntax_exception{syntax_exception::UNKNOWN_FUNCTION};
      }
      List tail;
      auto arg_it = std::make_move_iterator(expr->list.begin() + 1);
      auto arg_end = std::make_move_iterator(expr->list.end());
      for (; arg_it != arg_end; ++arg_it) {
        tail.push_back(eval(*arg_it, env));
      }
      ValuePtr args = std::make_unique<Value>(std::move(tail));

      return eval_fn(env, proc->symbol, std::move(args->list));
  }
}

}  // ns

#endif  // SLIGHTLISP_EVAL_HPP