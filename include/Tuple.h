#ifndef __TUPLE_H__
#define __TUPLE_H__

class Tuple
{
private:
    double m_x;
    double m_y;
    double m_z;
    double m_w;
public:
    Tuple(double x, double y, double z, double w);
    bool IsPoint() const;
    bool IsVector() const;
    ~Tuple();
};



#endif