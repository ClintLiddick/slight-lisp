#include <slightlisp/value.hpp>

#include <sstream>

using namespace slightlisp;

// default construct creates a list type
Value::Value()
    : tag{LIST}
{
}

Value::Value(Numeric num)
    : tag{NUMERIC}
    , num{num}
{
}

Value::Value(Symbol symbol)
    : tag{SYMBOL}
    , symbol{symbol}
{
}

Value::Value(List &&other_list)
    : tag{LIST}
    , list{std::move(other_list)}
{
}

Value::Value(bool boolean, Value::TYPE bool_tag)
    : tag{bool_tag}
    , boolean{boolean}
{
  if (bool_tag != Value::BOOL) {
    throw std::invalid_argument{
        "Value(bool, Value::TYPE) constructor is only for construtcing BOOL "
        "Values"};
  }
}

// movable
Value::Value(Value &&other)
    : tag{other.tag}
    , num{other.num}
    , symbol{other.symbol}
    , boolean{other.boolean}
    , list{std::move(other.list)}
{
}

Value &Value::operator=(Value &&other)
{
  tag = other.tag;
  num = other.num;
  symbol = other.symbol;
  list = std::move(other.list);
  boolean = other.boolean;
  return *this;
}

bool Value::operator==(const Value &other) const
{
  if (tag == other.tag) {
    switch (tag) {
      case NUMERIC:
        return num == other.num;
      case SYMBOL:
        return symbol == other.symbol;
      case LIST:
        if (list.size() != other.list.size()) {
          return false;
        } else {
          for (int i = 0; i < list.size(); ++i) {
            if (*list[i] != *other.list[i]) {
              return false;
            }
          }
          return true;
        }
      case BOOL:
        return boolean == other.boolean;
    }
  } else {
    return false;
  }
}

std::string Value::to_string() const
{
  std::stringstream ss;

  switch (tag) {
    case Value::NUMERIC:
      ss << num;
      return ss.str();
    case Value::SYMBOL:
      ss << symbol;
      return ss.str();
    case Value::LIST:
      ss << "(";
      for (auto i = list.begin(); i != list.end();) {
        ss << (**i).to_string();
        ++i;
        if (i != list.end()) {
          ss << " ";
        }
      }
      ss << ")";
      return ss.str();
  case Value::BOOL:
    ss << std::boolalpha << boolean;
    return ss.str();
  }
}

bool Value::operator!=(const Value &other) const { return !(*this == other); }

std::ostream &Value::operator<<(::std::ostream &os) const
{
  return os << to_string();
}
