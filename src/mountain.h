#include "main.h"

#ifndef MOUN_H
#define MOUN_H


class Mountain{
public:
    Mountain() {}
    Mountain(glm::vec3 pos, int siz, int type,float bloc);
    glm::vec3 position;
    float rotationx;
    float rotationy;
    float rotationz;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double siz;
    double block;
    int type;
private:
    VAO *object;
};

#endif // BALL_H
