#pragma once

#include "Color.h"
#include "Patterns/Pattern.h"
#include "utils/json.h"
#include <memory>

#include <iostream>

#define SET_VALUE(name) \
   if(obj[#name].isDouble()) { \
      name = obj[#name].asDouble(); \
   }
#define PRINT_VALUE(name) \
   std::cout << #name << ": " << name << std::endl



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

    Material() = default;
    Material(const Json::JSONObject& obj);

    void print() const {
       PRINT_VALUE(ambient);
       PRINT_VALUE(diffuse);
       PRINT_VALUE(specular);
       PRINT_VALUE(shininess);
       PRINT_VALUE(reflective);
       PRINT_VALUE(transparency);
       PRINT_VALUE(refraction_index);
       PRINT_VALUE(color);
    }

};
