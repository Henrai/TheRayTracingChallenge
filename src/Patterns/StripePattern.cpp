#include <Patterns/StripePattern.h>
#include <Color.h>
#include <Tuple.h>
#include <Shapes/Shape.h>

#include <cmath>

Color StripePattern::PatternAt(Tuple point) const {
    return  static_cast<int>(floor(point[0]))% 2 == 0 ? first : second;
}
