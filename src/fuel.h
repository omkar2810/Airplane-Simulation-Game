#include "main.h"
#include "polygon.h"
#include "frustum.h"
#ifndef FUEL_H
#define FUEL_H


class Fuel {
public:
    Fuel() {}
    Fuel(glm::vec3 pos);
    glm::vec3 position;
    glm::vec3 scale;
    // float rotation;
    int counter;
    Frustum base;
    Polygon poly;
    float ar_vel;
    void draw(glm::mat4 VP);
    glm::vec3 velocity;
    float gravity;
    glm::mat4 rotation;
    void tick(glm::vec3 pos);    
private:
    VAO *object;
};

#endif