#include "main.h"
using std::pair;
#ifndef RECT_H
#define RECT_H

class Rect {
public:
    Rect() {}
    Rect(float x, float y, color_t color,float sclx, float scly,float ang);
    glm::vec3 position;
    glm::vec3 scale;
    float rotation;
    void draw(glm::mat4 VP);
    void tick();
private:
    VAO *object;
};

#endif // BALL_H
