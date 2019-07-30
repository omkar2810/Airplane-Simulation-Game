#include "main.h"
#include "polygon.h"
#ifndef COM_H
#define COM_H


class Compass {
public:
    Compass() {}
    Compass(int a);
    glm::vec3 position;
    glm::vec3 scale;
    float rotation;
    std::vector<Polygon> poly;
    Polygon mark,tar;
    void draw(glm::mat4 VP);
    glm::vec3 velocity;
    float gravity;
    void tick(glm::vec3 pos1,glm::vec3 pos2);    
private:
    VAO *object;
};

#endif