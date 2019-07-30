#include "main.h"
#include "polygon.h"
#ifndef ALTI_H
#define ALTI_H


class Altitude {
public:
    Altitude() {}
    Altitude(int a);
    glm::vec3 position;
    glm::vec3 scale;
    float rotation;
    Polygon poly;
    void draw(glm::mat4 VP);
    glm::vec3 velocity;
    float gravity;
    void tick();    
private:
    VAO *object;
};

#endif