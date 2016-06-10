#include <slightlisp/env.hpp>

#include <slightlisp/special_forms.hpp>

namespace slightlisp
{
Env global_env()
{
  Env env;
  env["+"] = add;
  env[">"] = gt;

  return std::move(env);
}
}  // ns
