#include "main.h"
#include "missile.h"

Missile::Missile(glm::vec3 pos,glm::vec3 dir,glm::mat4 rotation,int type)
{
    GLfloat vertex_color_data[2000];
    int n=20;
    for(int i=0;i<n;i++)
    {
        vertex_color_data[9*i]   = rgb(225);
		vertex_color_data[9*i+1] = rgb(225);
		vertex_color_data[9*i+2] = rgb(225);

		vertex_color_data[9*i+3] = rgb(225);
		vertex_color_data[9*i+4] = rgb(225);
		vertex_color_data[9*i+5] = rgb(225);

		vertex_color_data[9*i+6] = rgb(225);
		vertex_color_data[9*i+7] = rgb(225);
		vertex_color_data[9*i+8] = rgb(225);

        vertex_color_data[9*(i+n)]   = rgb(225);
		vertex_color_data[9*(i+n)+1] = rgb(225);
		vertex_color_data[9*(i+n)+2] = rgb(225);

		vertex_color_data[9*(i+n)+3] = rgb(225);
		vertex_color_data[9*(i+n)+4] = rgb(225);
		vertex_color_data[9*(i+n)+5] = rgb(225);

		vertex_color_data[9*(i+n)+6] = rgb(225);
		vertex_color_data[9*(i+n)+7] = rgb(225);
		vertex_color_data[9*(i+n)+8] = rgb(225);
       
        vertex_color_data[9*(i+2*n)]   = rgb(0);
		vertex_color_data[9*(i+2*n)+1] = rgb(0);
		vertex_color_data[9*(i+2*n)+2] = rgb(225);

		vertex_color_data[9*(i+2*n)+3] = rgb(225);
		vertex_color_data[9*(i+2*n)+4] = rgb(220);
		vertex_color_data[9*(i+2*n)+5] = rgb(0);

		vertex_color_data[9*(i+2*n)+6] = rgb(200);
		vertex_color_data[9*(i+2*n)+7] = rgb(200);
		vertex_color_data[9*(i+2*n)+8] = rgb(0);
        
        vertex_color_data[9*(i+3*n)]   = rgb(0);
		vertex_color_data[9*(i+3*n)+1] = rgb(0);
		vertex_color_data[9*(i+3*n)+2] = rgb(225);

		vertex_color_data[9*(i+3*n)+3] = rgb(225);
		vertex_color_data[9*(i+3*n)+4] = rgb(220);
		vertex_color_data[9*(i+3*n)+5] = rgb(0);

		vertex_color_data[9*(i+3*n)+6] = rgb(200);
		vertex_color_data[9*(i+3*n)+7] = rgb(200);
		vertex_color_data[9*(i+3*n)+8] = rgb(0);
    }    
    this->type = type;

    if(type==1||type==3)
    {
        this->frus = Frustum(pos,{pos.x, pos.y ,pos.z-0.5},0.1,0,20,vertex_color_data);
        this->velocity = {-dir.x*0.08,-dir.y*0.08,-dir.z*0.08};
        this->position = {pos.x, pos.y, pos.z};
        this->rotation = rotation;
        this->dir = dir;
    }
    else if(type==2)
    {
        this->frus = Frustum(pos,{pos.x, pos.y ,pos.z-0.5},0.1,0,20,vertex_color_data);
        this->frus.rotationx = -3.14/2;
        this->velocity = {-dir.x*0.08,-dir.y*0.08,-dir.z*0.08};
        this->position = {pos.x, pos.y, pos.z};
        this->rotation = rotation;
        this->dir = dir;
    }  
}

void Missile::draw(glm::mat4 VP)
{
    this->frus.draw(VP,this->rotation);
}

void Missile::tick()
{
   this->position.x += this->velocity.x;
   this->position.y += this->velocity.y; 
   this->position.z += this->velocity.z; 

   this->frus.position.x += this->velocity.x;
   this->frus.position.y += this->velocity.y; 
   this->frus.position.z += this->velocity.z;

}