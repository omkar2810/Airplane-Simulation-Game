#include "main.h"
#include "polygon.h"
#include "frustum.h"
#ifndef SMOK_H
#define SMOK_H


class Smoke {
public:
    Smoke() {}
    Smoke(glm::vec3 pos,float ang);
    glm::vec3 position;
    glm::vec3 scale;
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