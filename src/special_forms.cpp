#include <slightlisp/special_forms.hpp>
#include <slightlisp/syntax_exception.hpp>

#include <stdexcept>

namespace slightlisp {

ValuePtr addValues(List &&args)
{
  if (args.size() != 2) {
    throw std::invalid_argument{"add requires two arguments"};
  }

  if (args[0]->tag != Value::NUMERIC || args[1]->tag != Value::NUMERIC) {
    throw std::invalid_argument{"add arguments must be numeric"};
  }

  return std::move(std::make_unique<Value>(args[0]->num + args[1]->num));
}

}  // ns
