#include <Patterns/RingPattern.h>
#include <Color.h>
#include <Tuple.h>
#include <Shapes/Shape.h>

#include <cmath>

Color RingPattern::PatternAt(Tuple point) const {
    return  static_cast<int>(floor(sqrt(point[0]*point[0] + point[2]*point[2]))) % 2 == 0 ? first : second;
}
