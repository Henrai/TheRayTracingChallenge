#pragma once 

#include "Tuple.h"
#include "Color.h"
#include "Material.h"

#include <algorithm>
#include <cmath>

#include <iostream>
#include <iomanip>

using namespace std;

struct PointLight
{
   Tuple position;
   Color intensity;
   PointLight(Tuple p, Color i) : position(p), intensity(i) {}
};

namespace lighting {
    static Color PhongLinghting(Material material, PointLight light, Tuple point, Tuple eyeV, Tuple normalV) {
        Color effectiveColor = material.color * light.intensity;
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