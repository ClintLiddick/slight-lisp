#ifndef SLIGHTLISP_SPECIAL_FORMS_HPP
#define SLIGHTLISP_SPECIAL_FORMS_HPP

#include <slightlisp/value.hpp>

namespace slightlisp
{
ValuePtr add(List &&args);
ValuePtr sub(List &&args);
ValuePtr gt(List &&args);
}

#endif  // SLIGHTLISP_SPECIAL_FORMS_HPP
