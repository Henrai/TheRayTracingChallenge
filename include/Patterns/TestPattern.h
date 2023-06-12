#pragma once 
#include "../Color.h"
#include "../Matrix.h"
#include "Pattern.h"

#include <memory>

class Tuple;
class Shape;

class TestPattern : public Pattern
{
    
public:
    TestPattern();
    Color PatternAt(Tuple point) const override;
};
