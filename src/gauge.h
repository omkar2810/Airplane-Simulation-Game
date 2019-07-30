#include "main.h"
#include "polygon.h"
#ifndef GAU_H
#define GAU_H


class Gauge {
public:
    Gauge() {}
    Gauge(int a);
    glm::vec3 position;
    glm::vec3 scale;
    float rotation;
    std::vector<Polygon> poly;
    void draw(glm::mat4 VP,float fuel);
    glm::vec3 velocity;
    float gravity;
    void tick();    
private:
    VAO *object;
};

#endif