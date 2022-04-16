#pragma once 
#include "../Color.h"
#include "../Matrix.h"
#include "Pattern.h"

#include <memory>

class Tuple;
class Shape;
class GradientPattern : public Pattern
{
public:
    GradientPattern(Color _first, Color _second): first(_first), second(_second), Pattern() {}
    Color PatternAt(Tuple point) const override;
    Color first, second;
};