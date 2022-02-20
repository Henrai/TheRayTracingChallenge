#include "Tuple.h"

Tuple::Tuple(double x, double y, double z, double w)
{
    m_x = x;
    m_y = y;
    m_z = z;
    m_w = w;
}

bool Tuple::IsPoint() const {
    return !IsVector();
}
bool Tuple::IsVector() const{
    return m_w == 0.0;
}

Tuple::~Tuple()
{
}