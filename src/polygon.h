#include "main.h"

#ifndef POLY_H
#define POLY_H

class Polygon{
public:
    Polygon(){}
    Polygon(int n, int part, color_t color,glm::vec3 scale,glm::vec3 position, float angle);
    color_t color;
    glm::vec3 scale;
    glm::vec3 position;
    float angle;
    void draw(glm::mat4 VP);
    void tick(float x, float y);
private:
    VAO *object;
};

#endif