#include "main.h"
#include "polygon.h"
#include "frustum.h"
#ifndef PARA_H
#define PARA_H


class Para {
public:
    Para() {}
    Para(glm::vec3 pos);
    glm::vec3 position;
    glm::vec3 scale;
    float rotation;
    std::vector<Frustum> vec;
    Polygon poly;
    void draw(glm::mat4 VP);
    glm::vec3 velocity;
    float gravity;
    void tick();    
private:
    VAO *object;
};

#endif