#include <Patterns/CheckerPattern.h>
#include <Color.h>
#include <Tuple.h>
#include <Shapes/Shape.h>

#include <cmath>

Color CheckerPattern::PatternAt(Tuple point) const {
    
    return static_cast<int>(floor(point[0]) + floor(point[1]) + floor(point[2]))%2 == 0 ? first : second;
}
