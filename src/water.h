#include "main.h"

#ifndef WATER_H
#define WATER_H


class Water{
public:
    Water() {}
    Water(glm::vec3 pos, int siz, int type, float block);
    glm::vec3 position;
    float rotationx;
    float rotationy;
    float rotationz;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
