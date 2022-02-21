#include <iostream>
#include <Tuple.h>
#include <MathUtil.h>

using namespace std;

struct Projectile{
    Tuple position;
    Tuple velocity;
    Projectile(Tuple p, Tuple v) {
        position = p;
        velocity = v;
    }
};

struct Enviroment{
    Tuple gravity;
    Tuple wind;
    Enviroment(Tuple g, Tuple w) {
        gravity = g;
        wind = w;
    }
};

Projectile tick(const Enviroment& env, const Projectile& proj) {
    return Projectile(
        proj.position  + proj.velocity,
        proj.velocity + env.gravity + env.wind
    );
}

int main() {
    Projectile p = Projectile(Tuple::Point(0,1,0), Tuple::Vector(1,1,0).normalize());
    Enviroment e = Enviroment(Tuple::Vector(0, -0.1, 0), Tuple::Vector(-0.01, 0,0)); 
    int tick_num = 0;
    while (p.position.Y() > 0.0)
    {
        p = tick(e, p);
        cout << tick_num <<": " << p.position << " " << p.velocity << endl;
        tick_num++;
    }
    
    return 0;
}
