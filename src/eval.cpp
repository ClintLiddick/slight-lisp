#include <slightlisp/eval.hpp>

#include <iterator>
#include <utility>

#include <slightlisp/syntax_exception.hpp>

namespace slightlisp
{
ValuePtr eval(ValuePtr expr, EnvPtr env)
{
  if (!expr) {
    throw std::invalid_argument{"null expression"};
  }

  switch (expr->tag) {
    case Value::SYMBOL:
      return std::move(std::make_unique<Value>(expr->symbol));
    case Value::NUMERIC:
      return std::move(std::make_unique<Value>(expr->num));
    case Value::LIST:
      return eval_list(std::forward<ValuePtr>(expr), env);
  }
}

inline ValuePtr eval_list(ValuePtr expr, EnvPtr env)
{
  if (expr->list.size() == 0) {
    throw syntax_exception{syntax_exception::UNEXPECTED_PARENS};
  }

  ValuePtr proc = eval(std::move(expr->list[0]), env);
  if (proc->tag != Value::SYMBOL) {
    throw syntax_exception{syntax_exception::UNKNOWN_FUNCTION,
                           proc->to_string()};
  }

  // TODO define
  // TODO quote

  if (proc->symbol == "if") {
    if (expr->list.size() != 4) {
      throw syntax_exception{syntax_exception::INVALID_IF_EXPRESSION};
    }

    ValuePtr cond_truth_value = eval(std::move(expr->list[1]), env);
    if (cond_truth_value->tag == Value::BOOL
        && cond_truth_value->boolean == false) {
      return eval(std::move(expr->list[3]), env);
    } else {
      return eval(std::move(expr->list[2]), env);
    }
  }
  else if (proc->symbol == "quote" || proc->symbol == "'") {
    if (expr->list.size() != 2) {
      throw std::invalid_argument{"quote requires one argument"};
    }
    return std::move(expr->list[1]);
  }
  else {
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

inline ValuePtr eval_if(ValuePtr expr, EnvPtr env)
{
  if (expr->list.size() == 0) {
    throw syntax_exception{syntax_exception::UNEXPECTED_PARENS};
  }

  ValuePtr if_sym = eval(std::move(expr->list[0]), env);
  if (if_sym->tag != Value::SYMBOL) {
    throw syntax_exception{syntax_exception::UNKNOWN_FUNCTION};
  }

  if (if_sym->symbol != "if") {
    throw std::invalid_argument{
        "expression must be in form (if COND IF_VALUE ELSE_VALUE)"};
  }
  // TODO empty value if no else expression
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
    throw syntax_exception{syntax_exception::UNKNOWN_FUNCTION, name};
  }
}

}  // ns
