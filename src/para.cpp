#include "main.h"
#include "para.h"

Para::Para(glm::vec3 pos)
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
    Frustum frus = Frustum({pos.x,pos.y,pos.z},{pos.x,pos.y,pos.z+0.5},0.8,0,50,vertex_color_data);
    frus.rotationx = -3.14/2;
    this->vec.push_back(frus);
    frus = Frustum({pos.x,pos.y-0.65,pos.z},{pos.x,pos.y-0.65,pos.z+0.5},0.45,0.45,4,vertex_color_data);
    frus.rotationx = -3.14/2;
    this->vec.push_back(frus);
}

void Para::draw(glm::mat4 VP)
{
    for(auto &x:this->vec)
        x.draw(VP,glm::mat4(1.0));    
}

void Para::tick()
{

    // this->position.y -= 0.001;
    
    for(auto &x:this->vec)
    {
        // x.position.y -= 0.001;
    }

}