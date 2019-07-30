#include "main.h"
#include "polygon.h"
#include "rect.h"
using std::vector;
#ifndef DIG_H
#define DIG_H

class Digit  {
public:
    Digit() {}
    Digit(float x, float y, color_t color,int digit);
    glm::vec3 position;
    glm::vec3 scale;
    void draw(glm::mat4 VP);
    void init_stor(int digit);
    int stor[7];
    vector<Rect> vec;
    float scx;
    float scy;
    void zoom(float sczoom);    
private:
    VAO *object;
};

#endif