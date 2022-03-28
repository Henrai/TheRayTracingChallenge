#include "Color.h"

float Color::R() const {
    return m_data[0];
}
float Color::G() const {
    return m_data[1];
}
float Color::B() const {
    return m_data[2];
}


std::ostream& operator<<(std::ostream& os, const Color& t)
{
    
    os << "RGB: ("<< t.R() << ", " << t.G() << ", " << t.B() <<")";
    return os;
}


const Color Color::RED(1.0, 0.0, 0.0); 
const Color Color::GREEN(0.0, 1.0, 0.0);
const Color Color::BLUE(0.0, 0.0, 1.0);
const Color Color::BLACK(0.0, 0.0, 0.0);
const Color Color::WHITE(1.0, 1.0, 1.0);
const Color Color::SHADOW(0.1, 0.1, 0.1);