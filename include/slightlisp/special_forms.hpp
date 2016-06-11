#ifndef SLIGHTLISP_SPECIAL_FORMS_HPP
#define SLIGHTLISP_SPECIAL_FORMS_HPP

#include <slightlisp/value.hpp>

namespace slightlisp
{
// math
ValuePtr add(List &&args);
ValuePtr sub(List &&args);
ValuePtr multi(List &&args);
ValuePtr div(List &&args);
// ValuePtr abs(List &&args);
// ValuePtr max(List &&args);
// ValuePtr min(List &&args);
// ValuePtr round(List &&args);
// comparison
ValuePtr gt(List &&args);
ValuePtr lt(List &&args);
ValuePtr eq(List &&args);
ValuePtr ge(List &&args);
ValuePtr le(List &&args);
ValuePtr not_(List &&args);
// list
// ValuePtr append(List &&args);
// ValuePtr apply(List &&args);
// ValuePtr begin(List &&args);
// ValuePtr car(List &&args);
// ValuePtr cdr(List &&args);
// ValuePtr cons(List &&args);
// ValuePtr length(List &&args);
// ValuePtr list(List &&args);
// query
// ValuePtr is_eq(List &&args);
// ValuePtr is_equal(List &&args);
// ValuePtr is_list(List &&args);
// ValuePtr is_number(List &&args);
// ValuePtr is_proc(List &&args);
// ValuePtr is_symbol(List &&args);
}

#endif  // SLIGHTLISP_SPECIAL_FORMS_HPP
