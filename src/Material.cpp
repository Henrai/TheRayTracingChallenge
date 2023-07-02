#include "Material.h"
#include "Color.h"
#include "Patterns/CheckerPattern.h"
#include <memory>
#include <utils/json.h>

Material::Material(const Json::JSONObject& obj) {
    if(!obj.isMap()) {
        return;
    }

    SET_VALUE(ambient)
    SET_VALUE(diffuse)
    SET_VALUE(specular)
    SET_VALUE(shininess)
    SET_VALUE(reflective)
    SET_VALUE(transparency)
    SET_VALUE(refraction_index)

    if (obj["color"].isList()) {
        auto colorList = obj["color"].asList();
        color = Color(
            colorList[0].asDouble(),
            colorList[1].asDouble(),
            colorList[2].asDouble()
        );
    }

    auto patternMap = obj["pattern"];
    if(patternMap.isMap()) {
        std::string name = patternMap["name"].asString();
        if (name == "CheckerPattern") {
            auto colorlist1 = patternMap["color_1"].asList();
            auto colorlist2 = patternMap["color_2"].asList();
            pattern = std::make_shared<CheckerPattern>(
                Color(colorlist1[0].asDouble(), colorlist1[1].asDouble(), colorlist1[2].asDouble()),
                Color(colorlist2[0].asDouble(), colorlist2[1].asDouble(), colorlist2[2].asDouble()));
        }
    }
    
}