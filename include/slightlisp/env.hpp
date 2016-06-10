#ifndef SLIGHTLISP_ENV_HPP
#define SLIGHTLISP_ENV_HPP

#include <functional>
#include <map>
#include <memory>
#include <slightlisp/value.hpp>

namespace slightlisp
{
// NOTE: the List parameter doesn't refer to LISP syntactical list
// but is rather a way to pass an unknown number of Value types to
// the calling function
using Env = std::map<Symbol, std::function<ValuePtr(List&&)>>;
using EnvPtr = std::shared_ptr<Env>;

Env global_env();

}  // ns

#endif  // SLIGHTLISP_ENV_HPP
