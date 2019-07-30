#include "main.h"

#ifndef FRUS_H
#define FRUS_H


class Frustum {
public:
    Frustum() {}
    Frustum(glm::vec3 pos1,glm::vec3 pos2, float scl1, float scl2,int n,GLfloat vertex_color_data[]);
    glm::vec3 position;
    glm::vec3 scale;
    float rotationx;
    float rotationy;
    float rotationz;
    void draw(glm::mat4 VP,glm::mat4 rotate);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif // BALL_H
