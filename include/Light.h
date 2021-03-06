#pragma once 

#include "Tuple.h"
#include "Color.h"
#include "Material.h"
#include "Shapes/Shape.h"

#include <algorithm>
#include <cmath>

#include <iostream>
#include <iomanip>
#include <memory>

using namespace std;

struct PointLight
{
   Tuple position;
   Color intensity;
   PointLight(Tuple p, Color i) : position(p), intensity(i) {}
};

namespace lighting {
    static Color PhongLinghting(std::shared_ptr<const Shape> object, PointLight light, Tuple point, Tuple eyeV, Tuple normalV, bool isShadowed = false){
        if (isShadowed) {
            return Color::SHADOW;
        }
        Material material = object->getMaterial();
        Color matrialColor = material.color;

        if (object != nullptr && material.pattern != nullptr) {
            matrialColor = material.pattern->PatternAtShape(object, point);            
        }

        Color effectiveColor = matrialColor * light.intensity;
        Tuple lightV = (light.position - point).normalize();
        Color ambient = effectiveColor * material.ambient;

        float lightDotNormal = lightV.Dot(normalV);
        Color diffuse = effectiveColor * material.diffuse * std::clamp( lightDotNormal, 0.0f, 1.0f);
        Tuple reflectV = -lightV.Reflect(normalV); 
        float reflectDotEye = std::clamp(reflectV.Dot(eyeV) , 0.0f, 1.0f);
        Color specular = light.intensity * material.specular * pow(reflectDotEye, material.shininess) ;
        return ambient + diffuse + specular;
    }
} // lighting