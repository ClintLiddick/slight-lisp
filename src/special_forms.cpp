#include <slightlisp/special_forms.hpp>
#include <slightlisp/syntax_exception.hpp>

#include <stdexcept>

namespace slightlisp
{
// math
ValuePtr add(List &&args)
{
  if (args.size() != 2) {
    throw std::invalid_argument{"add requires two arguments"};
  }

  if (args[0]->tag != Value::NUMERIC || args[1]->tag != Value::NUMERIC) {
    throw std::invalid_argument{"add arguments must be numeric"};
  }

  return std::move(std::make_unique<Value>(args[0]->num + args[1]->num));
}

ValuePtr sub(List &&args)
{
  if (args.size() != 2) {
    throw std::invalid_argument{"sub requires two arguments"};
  }

  if (args[0]->tag != Value::NUMERIC || args[1]->tag != Value::NUMERIC) {
    throw std::invalid_argument{"sub arguments must be numeric"};
  }

  return std::move(std::make_unique<Value>(args[0]->num - args[1]->num));
}

ValuePtr multi(List &&args)
{
  if (args.size() != 2) {
    throw std::invalid_argument{"multi requires two arguments"};
  }

  if (args[0]->tag != Value::NUMERIC || args[1]->tag != Value::NUMERIC) {
    throw std::invalid_argument{"multi arguments must be numeric"};
  }

  return std::move(std::make_unique<Value>(args[0]->num * args[1]->num));
}

ValuePtr div(List &&args)
{
  if (args.size() != 2) {
    throw std::invalid_argument{"div requires two arguments"};
  }

  if (args[0]->tag != Value::NUMERIC || args[1]->tag != Value::NUMERIC) {
    throw std::invalid_argument{"div arguments must be numeric"};
  }

  if (args[1]->num == 0.0) {
    throw std::invalid_argument{"division by zero"};
  }

  return std::move(std::make_unique<Value>(args[0]->num / args[1]->num));
}

// TODO
// ValuePtr abs(List &&args);
// ValuePtr max(List &&args);
// ValuePtr min(List &&args);
// ValuePtr round(List &&args);

// comparison
ValuePtr gt(List &&args)
{
  if (args.size() != 2) {
    throw std::invalid_argument{"> requires two arguments"};
  }

  if (args[0]->tag != args[1]->tag) {
    throw std::invalid_argument{"ordering arguments must be of same type"};
  }

  return std::move(std::make_unique<Value>(*args[0] > *args[1], Value::BOOL));
}

ValuePtr lt(List &&args)
{
  if (args.size() != 2) {
    throw std::invalid_argument{"> requires two arguments"};
  }

  if (args[0]->tag != args[1]->tag) {
    throw std::invalid_argument{"ordering arguments must be of same type"};
  }

  return std::move(std::make_unique<Value>(*args[0] < *args[1], Value::BOOL));
}

ValuePtr eq(List &&args)
{
  if (args.size() != 2) {
    throw std::invalid_argument{"= requires two arguments"};
  }

  if (args[0]->tag != args[1]->tag) {
    throw std::invalid_argument{"ordering arguments must be of same type"};
  }

  return std::move(std::make_unique<Value>(*args[0] == *args[1], Value::BOOL));
}

ValuePtr ge(List &&args)
{
  if (args.size() != 2) {
    throw std::invalid_argument{">= requires two arguments"};
  }

  if (args[0]->tag != args[1]->tag) {
    throw std::invalid_argument{"ordering arguments must be of same type"};
  }

  return std::move(std::make_unique<Value>(*args[0] >= *args[1], Value::BOOL));
}

ValuePtr le(List &&args)
{
  if (args.size() != 2) {
    throw std::invalid_argument{"<= requires two arguments"};
  }

  if (args[0]->tag != args[1]->tag) {
    throw std::invalid_argument{"ordering arguments must be of same type"};
  }

  return std::move(std::make_unique<Value>(*args[0] <= *args[1], Value::BOOL));
}

ValuePtr not_(List &&args)
{
  if (args.size() != 1) {
    throw std::invalid_argument{"not requires 1 argument"};
  }
  if (args[0]->tag == Value::BOOL && args[0]->boolean == false) {
    return std::move(std::make_unique<Value>(true, Value::BOOL));
  } else {
    return std::move(std::make_unique<Value>(false, Value::BOOL));
  }
}

// list
// TODO
// ValuePtr append(List &&args);
// ValuePtr apply(List &&args);
// ValuePtr begin(List &&args);
// ValuePtr car(List &&args);
// ValuePtr cdr(List &&args);
// ValuePtr cons(List &&args);
// ValuePtr length(List &&args);
// ValuePtr list(List &&args);

// query
// TODO
// ValuePtr is_eq(List &&args);
// ValuePtr is_equal(List &&args);
// ValuePtr is_list(List &&args);
// ValuePtr is_number(List &&args);
// ValuePtr is_proc(List &&args);
// ValuePtr is_symbol(List &&args);
}  // ns
