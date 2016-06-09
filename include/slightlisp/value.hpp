#ifndef SLIGHTLISP_VALUE_HPP
#define SLIGHTLISP_VALUE_HPP

#include <iostream>
#include <memory>
#include <vector>

namespace slightlisp
{
struct Value;

using ValuePtr = std::unique_ptr<Value>;
using Numeric = double;
using Symbol = std::string;
using List = std::vector<ValuePtr>;

struct Value {
  enum TYPE { NUMERIC, SYMBOL, LIST } tag;
  Numeric num;
  Symbol symbol;
  List list;

  // default construct creates a list type
  Value();
  explicit Value(Numeric num);
  explicit Value(Symbol symbol);
  explicit Value(List &&other_list);

  // non-copyable
  Value(const Value &other) = delete;
  Value &operator=(const Value &other) = delete;

  // movable
  Value(Value &&other);
  Value &operator=(Value &&other);

  bool operator==(const Value &other) const;

  std::string to_string() const;

  bool operator!=(const Value &other) const;

  std::ostream &operator<<(::std::ostream &os) const;
};

}  // ns
#endif  // SLIGHTLISP_VALUE_HPP
