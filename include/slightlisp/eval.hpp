#ifndef SLIGHTLISP_EVAL_HPP
#define SLIGHTLISP_EVAL_HPP

#include <slightlisp/env.hpp>
#include <slightlisp/value.hpp>

namespace slightlisp
{
ValuePtr eval(ValuePtr expr, EnvPtr env);
ValuePtr eval_list(ValuePtr expr, EnvPtr env);
ValuePtr eval_if(ValuePtr expr, EnvPtr env);

// NOTE: the List parameter doesn't refer to LISP syntactical list
// but is rather a way to pass an unknown number of Value types to
// the calling function
ValuePtr eval_fn(const EnvPtr env, const Symbol &name, List &&args);

}  // ns

#endif  // SLIGHTLISP_EVAL_HPP
