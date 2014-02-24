#include <stdexcept>

#include "add.h"
#include "mul.h"
#include "symbol.h"
#include "pow.h"
#include "rational.h"
#include "functions.h"

namespace CSymPy {

RCP<const Basic> Number::diff(const RCP<const Symbol> &x) const
{
    return zero;
}

} // CSymPy
