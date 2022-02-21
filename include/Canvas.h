#ifndef __CANVAS_H__
#define __CANVAS_H__

#include "Color.h"
#include <vector>
#include <ostream>

class Canvas {
private: 
    uint32_t width;
    uint32_t height;
    std::vector<std::vector<Color>> canvas;
    void writeHeader(std::ostream& os) const;
    void writeContent(std::ostream& os) const;
    void writeRow(std::ostream& os,  uint32_t index) const;
    void writeValue(std::ostream& os, size_t& cnt, double value) const;
    std::string GetAsPPMColor(double color) const;

public:
    Canvas(uint32_t w, uint32_t h);
    ~Canvas();

    uint32_t getWidth() const;
    uint32_t getHeight() const;

    std::vector<Color>& operator[](uint32_t row);

    friend std::ostream& operator<<(std::ostream& os, const Canvas& canvas);
};
#endif