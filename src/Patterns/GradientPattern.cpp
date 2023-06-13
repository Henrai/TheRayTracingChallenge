#include <Patterns/GradientPattern.h>
#include <Color.h>
#include <Tuple.h>
#include <Shapes/Shape.h>

#include <cmath>

Color GradientPattern::PatternAt(Tuple point) const {
    Color distance = second - first;
    double fraction = point[0] - floor(point[0]);
    return  first + distance * fraction;
}
