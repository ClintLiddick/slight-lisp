#include <slightlisp/env.hpp>

#include <slightlisp/special_forms.hpp>

namespace slightlisp
{
Env global_env()
{
  Env env;
  // math
  env["+"] = add;
  env["-"] = sub;
  env["*"] = multi;
  env["/"] = div;
  // comparison
  env["="] = eq;
  env["<"] = lt;
  env[">"] = gt;
  env["<="] = le;
  env[">="] = ge;
  env["not"] = not_;
  // list
  env["car"] = car;
  env["cdr"] = cdr;

  return std::move(env);
}
}  // ns
