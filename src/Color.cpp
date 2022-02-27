#include "Color.h"

Color::Color() {}
Color::Color(float r, float g, float b): Tuple(r,g,b,0.0){
}

Color::Color(const Color& color): Tuple(color.R(), color.G(), color.B(), 0.0){ 
}



float Color::R() const {
    return X();
}
float Color::G() const {
    return Y();
}
float Color::B() const {
    return Z();
}

Color Color::HadamardProduct(const Color& c) const {
    return Color(
        R() * c.R(),
        G() * c.G(),
        B() * c.B()
    );
}

const Color Color::RED(1.0, 0.0, 0.0); 
const Color Color::GREEN(0.0, 1.0, 0.0);
const Color Color::BLUE(0.0, 0.0, 1.0);
const Color Color::BLACK(0.0, 0.0, 0.0);
const Color Color::WHITE(1.0, 1.0, 1.0);