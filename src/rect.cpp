#include "rect.h"
#include "main.h"

Rect::Rect(float x, float y, color_t color,float sclx,float scly,float ang) {
    this->position = glm::vec3(x, y, 0);
    this->rotation = ang;
    this->scale = glm::vec3(sclx,scly,1.0);
    // Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
    // A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
    static const GLfloat vertex_buffer_data[] = {
        -1.0f,-1.0f,0.0f, // triangle 1 : begin
        -1.0f, 1.0f, 0.0f,
         1.0f, 1.0f,0.0f, // triangle 1 : end
         1.0f, 1.0f,0.0f,  // triangle 2 : begin
        -1.0f,-1.0f,0.0f,
         1.0f,-1.0f,0.0f, // triangle 2 : end
       
    };
    
    this->object = create3DObject(GL_TRIANGLES, 6, vertex_buffer_data, color, GL_FILL);
}

void Rect::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation), glm::vec3(0, 0, 1));
    glm::mat4 scale = glm::scale(this->scale);
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate*rotate*scale);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}