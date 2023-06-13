#pragma once

#include "Color.h"
#include "Patterns/Pattern.h"

#include <memory>

class Material
{
public:
    Color color = {Color::WHITE};
    double ambient {0.1f};
    double diffuse {0.9f};
    double specular {0.9f};
    double shininess {200.0f};
    double reflective {0.0f};
    double transparency {0.f};
    double refraction_index {1.f};

    std::shared_ptr<Pattern> pattern;

};
