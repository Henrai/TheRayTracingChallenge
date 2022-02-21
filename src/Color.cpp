#include "Color.h"

Color::Color() {}
Color::Color(double r, double g, double b): Tuple(r,g,b,0.0){
}

Color::Color(const Color& color): Tuple(color.R(), color.G(), color.B(), 0.0){ 
}



double Color::R() const {
    return X();
}
double Color::G() const {
    return Y();
}
double Color::B() const {
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