#include <Patterns/Pattern.h>
#include <Shapes/Shape.h>
#include <Tuple.h>

#include <memory>

Color Pattern::PatternAtShape(std::shared_ptr<const Shape> shape, Tuple worldPoint) const {
    Tuple objectPoint = shape->Transform().Inverse() *  worldPoint;
    Tuple patternPoint = transform.Inverse() * objectPoint;

    return PatternAt(patternPoint);
}