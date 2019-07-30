#include "main.h"
#include "frustum.h"
#ifndef MSL_H
#define MSL_H


class Missile {
public:
    Missile() {}
    Missile(glm::vec3 pos,glm::vec3 dir,glm::mat4 rotation, int type);
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 dir;
    glm::mat4 rotation;
    Frustum frus;
    int type;   
    void draw(glm::mat4 VP);
    glm::vec3 velocity;
    float gravity;
    void tick();    
private:
    VAO *object;
};

#endif