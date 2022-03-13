#include <iostream>
#include <Tuple.h>
#include <MathUtil.h>
#include <Canvas.h>
#include <fstream>
#include <vector>
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
    Canvas c(900, 550);
    Projectile p = Projectile(Tuple::Point(0,1,0), Tuple::Vector(1,1.8,0).normalize() * 11.25);
    Enviroment e = Enviroment(Tuple::Vector(0, -0.1, 0), Tuple::Vector(-0.01, 0,0)); 
    int tick_num = 0;
    
    while (p.position[1]> 0.0)
    {   
        c[(int)p.position[0]][550 - 1 - (int) p.position[1]] = Color::RED;
        p = tick(e, p);
        cout << tick_num <<": " << p.position << " " << p.velocity << endl;
        tick_num++;
    }
    
    ofstream out("projectile.ppm");
    out<<c;
    out.close();

    return 0;
}
