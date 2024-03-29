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
#include <string>

using namespace std;

struct PointLight
{
   std::string name;
   Tuple position;
   Color intensity;
   PointLight(Tuple p, Color i, const std::string& name = "") : position(p), intensity(i), name(name) {}
   void print() const {
        cout << "name: " << name << endl;
        cout << "position: " << position << endl;
        cout << "intensity: " << intensity << endl;
   }
};

namespace lighting {
    static Color PhongLinghting(std::shared_ptr<const Shape> object, PointLight light, Tuple point, Tuple eyeV, Tuple normalV, bool isShadowed = false){
       
       Color ambient, diffuse, specular;
        Material material = object->getMaterial();
        Color matrialColor = material.color;

        if (object != nullptr && material.pattern != nullptr) {
            matrialColor = material.pattern->PatternAtShape(object, point);            
        }

        Color effectiveColor = matrialColor * light.intensity;
        Tuple lightV = (light.position - point).normalize();
         ambient = effectiveColor * material.ambient;

        double lightDotNormal = lightV.Dot(normalV);

        if (lightDotNormal < 0.0 || isShadowed) {
            diffuse  = Color(0,0,0);
            specular = Color(0,0,0);
        } else {
            diffuse = effectiveColor * material.diffuse * std::clamp( (float)lightDotNormal, 0.0f, 1.0f);
            Tuple reflectV = -lightV.Reflect(normalV); 
            double reflectDotEye = std::clamp((float)reflectV.Dot(eyeV) , 0.0f, 1.0f);
            specular = light.intensity * material.specular * pow(reflectDotEye, material.shininess) ; 
        }
        return ambient + diffuse + specular;
    }
} // lighting