#include "main.h"
#include "polygon.h"
#include "frustum.h"
#ifndef CAN_H
#define CAN_H


class Canon {
public:
    Canon() {}
    Canon(glm::vec3 pos);
    glm::vec3 position;
    glm::vec3 scale;
    // float rotation;
    int counter;
    Frustum base,axil,pipe,arrow_head,arrow_body;
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