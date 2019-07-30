#include "main.h"
#include "frustum.h"
using std::vector;
#ifndef PLANE_H
#define PLANE_H


class Plane {
public:
    Plane() {}
    Plane(glm::vec3 pos);
    glm::vec3 position;
    float rotationx;
    float rotationy;
    float rotationz;
    glm::vec3 loc_x;
    glm::vec3 loc_y;
    glm::vec3 loc_z;
    glm::vec3 scale;
    glm::mat4 rotation;
    void draw(glm::mat4 VP);
    vector<Frustum> vec;
    void rotate(float x, float y,float z);
    void move(float x,float y,float z);
    void tick();
    double speed;
    float fuel;
    int barrel;
    int loop;
    float ver_vel;
    float hor_vel;
    float hor_acc;
    float ver_acc;
    int score;
private:
    VAO *object;
};

#endif // BALL_H
