#include "main.h"
#include "cannon.h"
#include "missile.h"
Canon::Canon(glm::vec3 pos)
{ 
    GLfloat vertex_color_data[2000];
    int n=50;
    // add color
    for(int i=0;i<50;i++)
    {
      //circle 1  
      {
        vertex_color_data[9*i]   = rgb(139);
		vertex_color_data[9*i+1] = rgb(69);
		vertex_color_data[9*i+2] = rgb(19);

		vertex_color_data[9*i+3] = rgb(160);
		vertex_color_data[9*i+4] = rgb(82);
		vertex_color_data[9*i+5] = rgb(45);

		vertex_color_data[9*i+6] = rgb(128);
		vertex_color_data[9*i+7] = rgb(0);
		vertex_color_data[9*i+8] = rgb(0);
      } 
      //cirle2 
      {
        vertex_color_data[9*(i+n)]   = rgb(139);
		vertex_color_data[9*(i+n)+1] = rgb(69);
		vertex_color_data[9*(i+n)+2] = rgb(19);

		vertex_color_data[9*(i+n)+3] = rgb(139);
		vertex_color_data[9*(i+n)+4] = rgb(69);
		vertex_color_data[9*(i+n)+5] = rgb(19);

		vertex_color_data[9*(i+n)+6] = rgb(139);
		vertex_color_data[9*(i+n)+7] = rgb(69);
		vertex_color_data[9*(i+n)+8] = rgb(19);
      }

      {
        vertex_color_data[9*(i+2*n)]   = rgb(255);	
        vertex_color_data[9*(i+2*n)+1] = rgb(255);
		vertex_color_data[9*(i+2*n)+2] = rgb(0);

		vertex_color_data[9*(i+2*n)+3] = rgb(255);
		vertex_color_data[9*(i+2*n)+4] = rgb(255);
		vertex_color_data[9*(i+2*n)+5] = rgb(0);

		vertex_color_data[9*(i+2*n)+6] = rgb(255);
		vertex_color_data[9*(i+2*n)+7] = rgb(255);
		vertex_color_data[9*(i+2*n)+8] = rgb(0);
      } 
      {  
        vertex_color_data[9*(i+3*n)]   = rgb(255);
		vertex_color_data[9*(i+3*n)+1] = rgb(87);
		vertex_color_data[9*(i+3*n)+2] = rgb(80);

		vertex_color_data[9*(i+3*n)+3] = rgb(255);
		vertex_color_data[9*(i+3*n)+4] = rgb(99);
		vertex_color_data[9*(i+3*n)+5] = rgb(71);

		vertex_color_data[9*(i+3*n)+6] = rgb(255);
		vertex_color_data[9*(i+3*n)+7] = rgb(215);
		vertex_color_data[9*(i+3*n)+8] = rgb(0);
      } 
    }
    this->position = pos;
    this->rotation = glm::mat4(1.0);
    this->base = Frustum({pos.x,pos.y-0.3,pos.z-1.2},{pos.x,pos.y-0.3,pos.z+1.2},1.0,1.0,4,vertex_color_data);  
    this->base.rotationz = -3.14/4;
    this->base.scale = {1.0,0.3,0.8};

      for(int i=0;i<50;i++)
    {
      //circle 1  
      {
        vertex_color_data[9*i]   = rgb(139);
		vertex_color_data[9*i+1] = rgb(139);
		vertex_color_data[9*i+2] = rgb(139);

		vertex_color_data[9*i+3] = rgb(139);
		vertex_color_data[9*i+4] = rgb(139);
		vertex_color_data[9*i+5] = rgb(139);

		vertex_color_data[9*i+6] = rgb(139);
		vertex_color_data[9*i+7] = rgb(139);
		vertex_color_data[9*i+8] = rgb(139);
      } 
      //cirle2 
      {
        vertex_color_data[9*(i+n)]   = rgb(139);
		vertex_color_data[9*(i+n)+1] = rgb(139);
		vertex_color_data[9*(i+n)+2] = rgb(139);

		vertex_color_data[9*(i+n)+3] = rgb(139);
		vertex_color_data[9*(i+n)+4] = rgb(139);
		vertex_color_data[9*(i+n)+5] = rgb(139);

		vertex_color_data[9*(i+n)+6] = rgb(139);
		vertex_color_data[9*(i+n)+7] = rgb(139);
		vertex_color_data[9*(i+n)+8] = rgb(139);
      }

      {
        vertex_color_data[9*(i+2*n)]   = rgb(85);	
        vertex_color_data[9*(i+2*n)+1] = rgb(105);
		vertex_color_data[9*(i+2*n)+2] = rgb(47);

		vertex_color_data[9*(i+2*n)+3] = rgb(85);
		vertex_color_data[9*(i+2*n)+4] = rgb(105);
		vertex_color_data[9*(i+2*n)+5] = rgb(47);

		vertex_color_data[9*(i+2*n)+6] = rgb(85);
		vertex_color_data[9*(i+2*n)+7] = rgb(105);
		vertex_color_data[9*(i+2*n)+8] = rgb(47);
      } 
      {  
        vertex_color_data[9*(i+3*n)]   = rgb(85);
		vertex_color_data[9*(i+3*n)+1] = rgb(107);
		vertex_color_data[9*(i+3*n)+2] = rgb(47);

		vertex_color_data[9*(i+3*n)+3] = rgb(85);
		vertex_color_data[9*(i+3*n)+4] = rgb(105);
		vertex_color_data[9*(i+3*n)+5] = rgb(47);

		vertex_color_data[9*(i+3*n)+6] = rgb(85);
		vertex_color_data[9*(i+3*n)+7] = rgb(105);
		vertex_color_data[9*(i+3*n)+8] = rgb(47);
      } 
    }

    this->axil = Frustum({pos.x,pos.y,pos.z},{pos.x,pos.y,pos.z-1.2-0.2},1.0,1.0,50,vertex_color_data);  
    // this->axil.rotationz = -3.14/4;
    this->axil.scale = {0.4,0.15,0.4};

    this->pipe = Frustum({pos.x,pos.y,pos.z},{pos.x,pos.y,pos.z+1},0.08,0.08,50,vertex_color_data);
    // this->pipe.rotationx = -3.14/6;
    this->counter = 0;

    for(int i=0;i<50;i++)
    {
      //circle 1  
      {
        vertex_color_data[9*i]   = rgb(227);
		vertex_color_data[9*i+1] = rgb(48);
		vertex_color_data[9*i+2] = rgb(84);

		vertex_color_data[9*i+3] = rgb(227);
		vertex_color_data[9*i+4] = rgb(48);
		vertex_color_data[9*i+5] = rgb(84);

		vertex_color_data[9*i+6] = rgb(227);
		vertex_color_data[9*i+7] = rgb(48);
		vertex_color_data[9*i+8] = rgb(84) ;    
        } 
      //cirle2 
      {
        vertex_color_data[9*(i+n)]   = rgb(217);
		vertex_color_data[9*(i+n)+1] = rgb(48);
		vertex_color_data[9*(i+n)+2] = rgb(84);

		vertex_color_data[9*(i+n)+3] = rgb(217);
		vertex_color_data[9*(i+n)+4] = rgb(48);
		vertex_color_data[9*(i+n)+5] = rgb(84);

		vertex_color_data[9*(i+n)+6] = rgb(217);
		vertex_color_data[9*(i+n)+7] = rgb(48);
		vertex_color_data[9*(i+n)+8] = rgb(84);
      }

      {
        vertex_color_data[9*(i+2*n)]   = rgb(255);	
        vertex_color_data[9*(i+2*n)+1] = rgb(255);
		vertex_color_data[9*(i+2*n)+2] = rgb(0);

		vertex_color_data[9*(i+2*n)+3] = rgb(255);
		vertex_color_data[9*(i+2*n)+4] = rgb(255);
		vertex_color_data[9*(i+2*n)+5] = rgb(0);

		vertex_color_data[9*(i+2*n)+6] = rgb(255);
		vertex_color_data[9*(i+2*n)+7] = rgb(255);
		vertex_color_data[9*(i+2*n)+8] = rgb(0);
      } 
      {  
        vertex_color_data[9*(i+3*n)]   = rgb(255);
		vertex_color_data[9*(i+3*n)+1] = rgb(87);
		vertex_color_data[9*(i+3*n)+2] = rgb(80);

		vertex_color_data[9*(i+3*n)+3] = rgb(255);
		vertex_color_data[9*(i+3*n)+4] = rgb(99);
		vertex_color_data[9*(i+3*n)+5] = rgb(71);

		vertex_color_data[9*(i+3*n)+6] = rgb(255);
		vertex_color_data[9*(i+3*n)+7] = rgb(215);
		vertex_color_data[9*(i+3*n)+8] = rgb(0);
      } 
    }
    ar_vel = 0.05;
    this->arrow_head = Frustum({pos.x,pos.y+6,pos.z-0.4},{pos.x,pos.y+6,pos.z+0.4-0.4},0.5,0.5,3,vertex_color_data);
    this->arrow_head.rotationx = 3.14;
    this->arrow_head.scale = {2.0,2.0,2.0};
    this->arrow_body = Frustum({pos.x,pos.y+8,pos.z-0.4},{pos.x,pos.y+8,pos.z+0.4-0.4},0.5,0.5,4,vertex_color_data);
    this->arrow_body.rotationx = 3.14;
    this->arrow_body.rotationz = 3.14/4;
    this->arrow_body.scale = {0.5*2.0,2.5*2.0,0.8*2.0};
}

void Canon::draw(glm::mat4 VP)
{   
   this->base.draw(VP,glm::mat4(1.0));      
   this->axil.draw(VP,this->rotation);      
   this->pipe.draw(VP,this->rotation);      
   this->arrow_head.draw(VP,glm::mat4(1.0)); 
   this->arrow_body.draw(VP,glm::mat4(1.0)); 
}

void Canon::tick(glm::vec3 pos)
{
    glm::vec3 dir = {pos.x-this->position.x,pos.y-this->position.y,pos.z-this->position.z};
    float mod = sqrt(dir.x*dir.x + dir.y*dir.y + dir.z*dir.z);
    dir = {dir.x/mod,dir.y/mod,dir.z/mod};
    
    glm::vec3 axis = glm::cross(glm::vec3(0,0,1),dir);
    float theta = acos(glm::dot(glm::vec3(0,0,1),dir));
    this->rotation = glm::rotate(theta,axis);
    this->counter++;

    // glm::vec3 arr = {pos.x-this->position.x,pos.y,pos.z - this->position.z};
    // arr = glm::normalize(arr);    
    // this->arrow_head.position.x -= arr.x
    if(this->arrow_head.position.y <= this->position.y + 2)
    {
        this->ar_vel*=-1;
    }

    if(this->arrow_head.position.y >= this->position.y + 7)
        this->ar_vel*=-1;
    this->arrow_body.position.y += this->ar_vel;
    this->arrow_head.position.y += this->ar_vel;

}