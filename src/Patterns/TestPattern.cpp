#include "Patterns/Pattern.h"
#include <Patterns/TestPattern.h>
#include <Color.h>
#include <Tuple.h>
#include <Shapes/Shape.h>

#include <cmath>

TestPattern::TestPattern(): Pattern() {}

Color TestPattern::PatternAt(Tuple point) const {
    return  Color(point[0],point[1],point[2]);
}
