#include <Canvas.h>
#include <Matrix.h>
#include <Transformation.h>
#include <Tuple.h>
#include <Color.h>

#include <fstream>
using namespace std;

int main() {
    Canvas canvas(500, 500);
    float rotationAngle = M_PI/8;
    Matrix4 translate = matrix::Translation(250.f, 250.f, 0.f);
    Matrix4 scale = matrix::Scale(200.f, 200.f, 1.f);
    Matrix4 transM = translate * scale ;

    Tuple pos = Tuple::Point(0.f,1.f,0.f);
    
    for (size_t i = 0; i < 16; i++) {
        
        Tuple drawPoint = transM*pos;

        cout<<pos<<" "<< drawPoint<<endl;
        canvas[drawPoint.X()][drawPoint.Y()] = Color::WHITE;

        pos =  matrix::RotationZ(rotationAngle) * pos;
    }  

    ofstream out("clock.ppm");
    out<<canvas;
    out.close();

    return 0;
}