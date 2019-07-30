#include "main.h"
#include "speed.h"

Speed::Speed(int a)
{ 
    this->meter = Polygon(50,2,{25,25,26},{0.8,0.8,0.8},{0,-3.8,0},-3.14/2);
    // this->needle = Polygon(3,1,{253,253,236},{0.1,0.5,1.0},{0,0.0,0},3.14/2);

    static const GLfloat vertex_buffer_data[] = {
         0.2, 0.0, 0,
        -0.2, 0.0, 0,
         0.0, 0.6, 0,
    };

    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data,{253,253,236}, GL_FILL);
    this->scale = {0.6,1.0,1.0};
    this->position = {0.0,-3.6,0.0};
    this->rotation = 3.14/2;
}

void Speed::draw(glm::mat4 VP,float speed)
{

    this->meter.draw(VP);
    this->rotation = -((speed-0.04)/0.08)*3.14; 

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float)(this->rotation), glm::vec3(0, 0, 1));
    glm::mat4 scale = glm::scale(this->scale);

    Matrices.model *= (translate*rotate*scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}