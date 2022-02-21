#include "Color.h"

Color::Color() {}
Color::Color(double r, double g, double b): Tuple(r,g,b,0.0){
}

Color::Color(const Color& color): Tuple(color.Red(), color.Green(), color.Blue(), 0.0){ 
}



double Color::Red() const {
    return X();
}
double Color::Green() const {
    return Y();
}
double Color::Blue() const {
    return Z();
}

Color Color::HadamardProduct(const Color& c) const {
    return Color(
        Red() * c.Red(),
        Green() * c.Green(),
        Blue() * c.Blue()
    );
}
