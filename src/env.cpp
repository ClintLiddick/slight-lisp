#include <slightlisp/env.hpp>

#include <slightlisp/special_forms.hpp>

namespace slightlisp
{
Env global_env()
{
  Env env;
  env["+"] = add;
  env["-"] = sub;
  env["*"] = multi;
  env["/"] = div;
  env["="] = eq;
  env["<"] = lt;
  env[">"] = gt;
  env["<="] = le;
  env[">="] = ge;
  env["not"] = not_;

  return std::move(env);
}
}  // ns
