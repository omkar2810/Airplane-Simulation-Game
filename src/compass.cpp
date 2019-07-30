#include "main.h"
#include "compass.h"

Compass::Compass(int a)
{ 
    glm::vec3 posi(-2.6,-2.3,0);
    Polygon pol = Polygon(50,1,{255,0,0},glm::vec3(0.6,0.6,0),posi,0);
    this->poly.push_back(pol);   
    pol = Polygon(50,1,{0,0,0},glm::vec3(0.55,0.55,0),posi,0);
    this->poly.push_back(pol);
    pol = Polygon(4,1,{26,26,26},glm::vec3(0.8,0.8,1.0),glm::vec3(posi.x,posi.y-1.2,0),3.14/4);
    this->poly.push_back(pol);
    this->mark = Polygon(20,1,{226,226,0},glm::vec3{0.05,0.05,0.05},glm::vec3(posi.x,posi.y-0.8,0),0);
    this->tar = Polygon(20,1,{226,0,0},glm::vec3{0.05,0.05,0.05},glm::vec3(posi.x,posi.y-1,0),0);
    static const GLfloat vertex_buffer_data[] = {
         0.2, 0.0, 0,
        -0.2, 0.0, 0,
         0.0, 0.6, 0,
         0.2, 0.0, 0,
        -0.2, 0.0, 0,
         0.0, -0.6, 0,
    };
    static const GLfloat vertex_color_data[] = {
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        1.0,0.0,0.0,
        0.0,0.0,1.0,
        0.0,0.0,1.0,
        0.0,0.0,1.0,
    };
    this->scale = {0.6,0.6,1.0};
    this->position = posi;
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data,vertex_color_data, GL_FILL);
    this->rotation = 0;
}

void Compass::draw(glm::mat4 VP)
{
    for(auto &x:this->poly)
        x.draw(VP);
    this->mark.draw(VP);
    this->tar.draw(VP);

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float)(this->rotation), glm::vec3(0, 0, 1));
    glm::mat4 scale = glm::scale(this->scale);

    Matrices.model *= (translate*rotate*scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

}

void Compass::tick(glm::vec3 pos1,glm::vec3 pos2)
{
    this->mark.position.x = -2.6 + 0.005*pos1.x;
    this->mark.position.y = -3.5 - 0.005*pos1.z;
    this->tar.position.x = -2.6 + 0.005*(pos2.x);
    this->tar.position.y = -3.5 - 0.005*(pos2.z);

}