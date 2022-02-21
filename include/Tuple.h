#ifndef __TUPLE_H__
#define __TUPLE_H__

#include <ostream>

class Tuple
{
private:
    double m_x;
    double m_y;
    double m_z;
    double m_w;
public:
    Tuple(double x, double y, double z, double w);
    Tuple(const Tuple& t);
    Tuple();

    double X() const;
    double Y() const;
    double Z() const;
    double W() const;


    bool IsPoint() const;
    bool IsVector() const;
    
    Tuple operator+(const Tuple& t) const;
    Tuple operator-(const Tuple& t) const;
    bool operator==(const Tuple& t) const;
    Tuple operator*(double scalar) const;
    Tuple operator/(double scalar) const;

    Tuple operator-() const;

    double Dot(const Tuple& t) const;
    Tuple Cross(const Tuple& t) const;
    double Magnitude() const;
    Tuple normalize() const;
    
    virtual ~Tuple();

    static Tuple Point(double x, double y, double z);
    static Tuple Vector(double x, double y, double z);

    friend std::ostream& operator<<(std::ostream& os, const Tuple& t);
};



#endif