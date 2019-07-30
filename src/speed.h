#include "main.h"
#include "polygon.h"
#ifndef SPD_H
#define SPD_H


class Speed {
public:
    Speed() {}
    Speed(int a);
    glm::vec3 position;
    glm::vec3 scale;
    float rotation;
    Polygon meter;
    Polygon needle;
    void draw(glm::mat4 VP,float speed);
    void tick();    
private:
    VAO *object;
};

#endif