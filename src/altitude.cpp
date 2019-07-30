#include "main.h"
#include "altitude.h"

Altitude::Altitude(int a)
{ 
    this->position = {-3.7,-2.8,0};
    this->poly = Polygon(50,1,{255,0,0},glm::vec3(0.15,0.15,0),glm::vec3(-3.7,-3.6,0),0);   

    static const GLfloat vertex_buffer_data[] = {
        -1.0,1.0,0.0,
         1.0,1.0,0.0,
        -1.0,-1.0,0.0,
        -1.0,-1.0,0.0,
         1.0,-1.0,0.0,
         1.0,1.0,0.0,   
    };

    this->scale = {0.05,1.0,1.0};
    this->object = create3DObject(GL_TRIANGLES, 6*3, vertex_buffer_data,{0,0,0}, GL_FILL);
    this->rotation = 0;
}

void Altitude::draw(glm::mat4 VP)
{
    
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float)(this->rotation), glm::vec3(0, 0, 1));
    glm::mat4 scale = glm::scale(this->scale);
    Matrices.model *= (translate*rotate*scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

    this->poly.draw(VP);

}

void Altitude::tick()
{
//    this->position.x += this->velocity.x;
//    this->position.y += this->velocity.y; 
//    this->position.z += this->velocity.z; 
}