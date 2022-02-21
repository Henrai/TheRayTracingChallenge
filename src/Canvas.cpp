#include "Canvas.h"
#include "Color.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <cmath>

Canvas::Canvas(uint32_t w, uint32_t h) {
    width = w;
    height = h;
    canvas.assign(w, std::vector<Color>(h, Color::BLACK));
}

Canvas::~Canvas(){}

uint32_t Canvas::getWidth() const {
    return width;

}
uint32_t Canvas::getHeight() const {
    return height;
}

std::vector<Color>& Canvas::operator[](uint32_t row) {
    return canvas[row];
}

void Canvas::writeHeader(std::ostream& os) const{
    os << "P3" << std::endl 
       << width <<" "<< height << std::endl 
       << 255 << std::endl;
}
void Canvas::writeContent(std::ostream& os) const{
    for (size_t i = 0; i < height; i++) {
        writeRow(os, i);
    }
}

void Canvas::writeRow(std::ostream& os, uint32_t index) const{
    size_t cnt = 0;
    for (size_t i = 0; i < width; i++) {
        writeValue(os, cnt, canvas[i][index].R());
        writeValue(os, cnt, canvas[i][index].G());
        writeValue(os, cnt, canvas[i][index].B());
    }
    os<<std::endl;
}

void Canvas::writeValue(std::ostream& os, size_t& cnt, double value) const {
    std::string s = GetAsPPMColor(value);
    if (cnt + s.size() + 1 > 70) {
        cnt = 0;
        os << std::endl;
    }
    if (cnt > 0) os << " ";
    os << s;
    cnt += s.size() + 1;
}

std::string Canvas::GetAsPPMColor(double color) const {
    return std::to_string(std::clamp((int)std::round(color * 255.f), 0, 255));
}

std::ostream& operator<<(std::ostream& os, const Canvas& canvas)
{
   canvas.writeHeader(os);
   canvas.writeContent(os);
   return os;
}

